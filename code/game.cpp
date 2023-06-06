#include "game.hpp"

Game::Game(std::shared_ptr<sf::RenderWindow> &window, sf::Font &font, unsigned int gameMode) : window(window), font(font), gameMode(gameMode)
{
    // set available items
    itemTypes = {SpeedUp(), OpponentSlow(), Bomb(), Dash(), Reverse(), Stun(), Swap()};
    car1 = CarSprite("Black", 80, 50, 2.5, 4);
    car2 = CarSprite("Red", 850, 850, 2.5, 8);
    loadAssets();
    resetCarsPosition();
    if (gameMode == 0)
    {
        totalPlayTime = sf::seconds(0);
    }
    if (gameMode == 1)
    {
        flag = Flag(480, 470);
        flagHolder = 0;
        timeLimit = sf::seconds(30);
        flag.setTexture(flag.getTexture());
        flag.setScale(1.75, 1.75);
    }
    clock.restart();
    sinceLastItemSpawn.restart();
}

void Game::loadAssets()
{
    // Set view
    view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
    loadFont();
    loadMap();
    loadSound();
    car1PointsText.setString(std::to_string(car1.getCarObj().getPoint()));
    car2PointsText.setString(std::to_string(car2.getCarObj().getPoint()));
}

void Game::loadFont()
{
    // Create text
    timerText = sf::Text("", font, STATS_FONT_SIZE);
    timerText.setPosition(TIMER_X, TIMER_Y);
    car1PointsText = sf::Text("", font, STATS_FONT_SIZE);
    car1PointsText.setPosition(CAR1_POINTS_X, CAR1_POINTS_Y);
    car2PointsText = sf::Text("", font, STATS_FONT_SIZE);
    car2PointsText.setPosition(CAR2_POINTS_X, CAR2_POINTS_Y);
    message = sf::Text("", font, STATS_FONT_SIZE);
}

void Game::loadMap()
{
    // Load map
    mapTexture.loadFromFile(ASSET_PATHS_HPP::MAP_LIST[mapIndex]);
    map.setTexture(mapTexture, true);
    map.setScale(sf::Vector2f(MAP_SCALE, MAP_SCALE));
    map.setOrigin(190, 230);
}

void Game::loadSound()
{
    // Load game start sound
    startSoundBuffer.loadFromFile(ASSET_PATHS_HPP::GAMESTART_SFX);
    startSound.setBuffer(startSoundBuffer);
    startSound.setVolume(60);
    startSound.play();
    // Load music
    musicBuffer.loadFromFile(ASSET_PATHS_HPP::MUSIC_LIST[musicIndex]);
    music.setBuffer(musicBuffer);
    music.setLoop(true);
    music.setVolume(20);
    // Load crash sound
    crashSoundBuffer.loadFromFile(ASSET_PATHS_HPP::CRASH_SFX);
    crashSound.setBuffer(crashSoundBuffer);
    // Play music
    music.play();
}

void Game::nextMap()
{
    mapIndex++;
    mapIndex = mapIndex % ASSET_PATHS_HPP::MAP_LIST.size();
}

void Game::nextMusic()
{
    musicIndex++;
    musicIndex = musicIndex % ASSET_PATHS_HPP::MUSIC_LIST.size();
}

void Game::resetCarsPosition()
{
    car1.resetCar();
    car2.resetCar();
}

void Game::nextRound(unsigned int winner)
{
    resetCarsPosition();
    startSound.play();
    car1PointsText.setString(std::to_string(car1.getCarObj().getPoint()));
    car2PointsText.setString(std::to_string(car2.getCarObj().getPoint()));
    countDown(winner);
}

void Game::spawnItem()
{
    // TODO: not spawn on player or other item
    std::srand(std::time(nullptr));
    float xItemPos = BORDER_LEFT + 30 + (755 * std::rand() % static_cast<int>(BORDER_RIGHT - BORDER_LEFT - 60));
    float yItemPos = BORDER_TOP + 30 + (521 * std::rand() % static_cast<int>(BORDER_BOTTOM - BORDER_TOP - 60));
    sf::Clock itemClock = sf::Clock();

    itemsOnMap.push_back(
        {itemTypes[static_cast<int>(xItemPos) % static_cast<int>(yItemPos) % itemTypes.size()],
         itemClock});
    itemsOnMap[itemsOnMap.size() - 1].first.setPosition(xItemPos, yItemPos);

    // this somehow prevents error when copying texture
    itemsOnMap[itemsOnMap.size() - 1].first.setTexture(itemTypes[static_cast<int>(xItemPos) % static_cast<int>(yItemPos) % itemTypes.size()].getTexture());
}

void Game::drawObjects(bool drawCar, bool drawTimer, bool drawPoints, bool drawFlag, bool drawItems)
{
    window->draw(map);
    if (drawCar)
    {
        window->draw(car1);
        window->draw(car2);
    }
    if (drawTimer)
        window->draw(timerText);
    if (drawPoints)
    {
        window->draw(car1PointsText);
        window->draw(car2PointsText);
    }
    if (drawFlag)
        window->draw(this->flag);
    if (drawItems)
    {
        for (auto &item : itemsOnMap)
            window->draw(item.first);
    }
}

bool Game::checkCarCollisions()
{
    if (car1.checkCollision(car2))
    {
        crashSound.play();
        handleCarCollision();
        return true;
    }
    return false;
}

void Game::handleCarCollision()
{
    sf::Vector2f relPosition = car2.getPosition() - car1.getPosition();
    sf::Vector2f relVelocity = car1.getVelocity() - car2.getVelocity();

    // Compute the dot product of the relative velocity and the relative position vectors
    float dotProduct = relVelocity.x * relPosition.x + relVelocity.y * relPosition.y;
    float dotProduct2 = car1.getVelocity().x * car2.getVelocity().x + car1.getVelocity().y * car2.getVelocity().y;

    if (dotProduct2 < 0)
    {
        // Cars are going in opposite directions
        sf::Vector2f temp = car1.getVelocity();
        car1.getPushed(car2.getVelocity().x, car2.getVelocity().y);
        car2.getPushed(temp.x, temp.y);
    }
    else // if (dotProduct2 > 0)
    {
        // not a head-on collision
        if (dotProduct >= 0)
        {
            // car1 is driving towards car2
            sf::Vector2f temp = car1.getVelocity();
            car1.push(car2.getVelocity().x, car2.getVelocity().y);
            car2.getPushed(temp.x, temp.y);
        }
        else if (dotProduct < 0)
        {
            // car2 is driving towards car1
            sf::Vector2f temp = car1.getVelocity();
            car1.getPushed(car2.getVelocity().x, car2.getVelocity().y);
            car2.push(temp.x, temp.y);
        }
    }
}

void Game::handleItemAction()
{
    for (auto itemIt = itemsOnMap.begin(); itemIt != itemsOnMap.end(); itemIt++)
    {
        if (itemIt->second.getElapsedTime().asSeconds() > 10) // if item is on map for more than 5 seconds
        {
            itemsOnMap.erase(itemIt);
            break;
        }
        if (car1.checkCollision(itemIt->first))
        {
            if (!itemIt->first.getUseOnSelf())
                useItem(car2, itemIt->first);
            else
                useItem(car1, itemIt->first);
            itemsOnMap.erase(itemIt);
            break;
        }
        if (car2.checkCollision(itemIt->first))
        {
            if (!itemIt->first.getUseOnSelf())
                useItem(car1, itemIt->first);
            else
                useItem(car2, itemIt->first);
            itemsOnMap.erase(itemIt);
            break;
        }
    }
}

void Game::useItem(CarSprite &car, Item &item)
{
    if (item.getExplode())
        car.explosion();
    if (item.getStun())
        car.stop();
    if (item.getSwap())
    {
        float tempX = car1.getX();
        float tempY = car1.getY();
        car1.setPos(car2.getX(), car2.getY());
        car2.setPos(tempX, tempY);
    }

    else
    {
        if (item.getMaxSpeed() >= 0)
            car.getCarObj().setMaxSpeed(item.getMaxSpeed());

        if (item.getAcceleration() >= 0)
            car.getCarObj().setAcceleration(item.getAcceleration());

        if (item.getReverseSteering())
            car.reverseSteering();
        car.usedItem(item.getDuration());
    }
}

bool Game::carCrossedLine(const CarSprite &car)
{
    return !(car.getX() > BORDER_LEFT && car.getY() > BORDER_TOP && car.getX() < BORDER_RIGHT && car.getY() < BORDER_BOTTOM);
}

void Game::countDown(unsigned int winner)
{
    sf::Text countDownText;
    sf::Text winnerText;
    countDownText.setCharacterSize(300);
    countDownText.setFont(font);
    if (winner > 0)
        winnerText.setString(" Point\n  for  \nPlayer " + std::to_string(winner));
    else if (winner == 0)
        winnerText.setString("Tieeeeeeeeeeeee!!!");
    winnerText.setCharacterSize(50);
    winnerText.setFont(font);
    winnerText.setPosition(388, 135);
    crashSound.setPitch(2);
    view.setCenter((3090 + 80 + 850) / 8, (3000 + 50 + 850) / 8);
    window->setView(view);
    std::vector<sf::Vector2f> nextPositions = {sf::Vector2f(710, 300), sf::Vector2f(430, 550), sf::Vector2f(150, 300)};
    for (int i = 3; i > 0; i--)
    {
        countDownText.setString(std::to_string(i));
        countDownText.setPosition(nextPositions[i - 1]);
        window->clear(sf::Color::Black);
        drawObjects();
        window->draw(countDownText);
        window->draw(winnerText);
        window->display();
        crashSound.play();
        sf::sleep(sf::milliseconds(500));
    }
    crashSound.setPitch(1);
    clock.restart();
}

void Game::printMsg(const std::string &msg, float x, float y)
{
    message.setString(msg);
    message.setPosition(x, y);
    message.setFillColor(sf::Color::Black);
    window->draw(message);
    window->display();
    sf::sleep(sf::seconds(1));
}

void Game::duelEndCondition()
{
    bool car1CrossedLine = carCrossedLine(car1);
    bool car2CrossedLine = carCrossedLine(car2);
    unsigned int roundWinner = 0;
    if (car1CrossedLine)
    {
        if (!car2CrossedLine)
        {
            car2.getCarObj().setPoint();
            roundWinner = 2;
        }
        totalPlayTime += clock.getElapsedTime();
        nextRound(roundWinner);
    }
    else if (car2CrossedLine)
    {
        totalPlayTime += clock.getElapsedTime();
        car1.getCarObj().setPoint();
        roundWinner = 1;
        nextRound(roundWinner);
    }
}

void Game::loadDuelRound()
{
    sf::Time elapsed = clock.getElapsedTime() + totalPlayTime;
    int min = static_cast<int>(elapsed.asSeconds()) / 60;
    int sec = static_cast<int>(elapsed.asSeconds()) % 60;
    timerText.setString((min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + ":" + (sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec)));

    if (sinceLastItemSpawn.getElapsedTime().asSeconds() > 2 && itemsOnMap.size() < itemCap)
    {
        spawnItem();
        sinceLastItemSpawn.restart();
    }

    car1.checkItemReset();
    car2.checkItemReset();
    car1.move();
    car2.move();

    checkCarCollisions();
    handleItemAction();
    duelEndCondition();

    view.setCenter((car1.getX() + car2.getX() + 3090) / 8, (car1.getY() + car2.getY() + 3000) / 8);
    window->clear(sf::Color::Black);
    window->setView(view);
    drawObjects(1, 1, 1, 0, 1);
    window->display();
}

void Game::checkBounceCondition()
{
    // If car hit the wall, bounce it back to the map using getPushed function
    if (carCrossedLine(car1))
        car1.getPushed(-car1.getVelocity().x, -car1.getVelocity().y);
    if (carCrossedLine(car2))
        car2.getPushed(-car2.getVelocity().x, -car2.getVelocity().y);
}

void Game::checkFlag()
{

    if (flagHolder != 0)
    {
        if (flagHolder == 1)
        {
            flag.setPosition(car1.getX(), car1.getY());
        }
        else
        {
            flag.setPosition(car2.getX(), car2.getY());
        }
        return;
    }
    if (car1.checkCollision(flag))
    {
        flagHolder = 1;
    }
    if (car2.checkCollision(flag))
    {
        flagHolder = 2;
    }
}

void Game::tagEndCondition()
{

    if (flagHolder == 1)
        car1.getCarObj().setPoint();

    else if (flagHolder == 2)
        car2.getCarObj().setPoint();

    flag.setPosition(480, 470);

    flagHolder = 0;
    nextRound(flagHolder);
}

void Game::loadTagRound()
{
    sf::Time elapsed = clock.getElapsedTime();
    // calculate time left
    int min = static_cast<int>(timeLimit.asSeconds() - elapsed.asSeconds()) / 60;
    int sec = static_cast<int>(timeLimit.asSeconds() - elapsed.asSeconds()) % 60 + 1;
    if (min == 0 && sec < 0)
        tagEndCondition();

    timerText.setString((min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + ":" + (sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec)));
    if (sinceLastItemSpawn.getElapsedTime().asSeconds() > 2 && itemsOnMap.size() < itemCap)
    {
        spawnItem();
        sinceLastItemSpawn.restart();
    }

    car1.checkItemReset();
    car2.checkItemReset();
    car1.move();
    car2.move();

    // if car1 hit car2, and flag is belong to someone, give the flag to other car
    if (checkCarCollisions() && flagHolder != 0)
        flagHolder = 3 - flagHolder;
    handleItemAction();
    checkFlag();
    checkBounceCondition();

    view.setCenter((car1.getX() + car2.getX() + 3090) / 8, (car1.getY() + car2.getY() + 3000) / 8);
    window->clear(sf::Color::Black);
    window->setView(view);
    drawObjects(1, 1, 1, 1, 1);
    window->display();
}

int Game::handleEvent()
{
    // Check if ESC key is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        view.setCenter(512, 512);
        window->setView(view);
        return 0;
    }
    bool UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    if ((UpPressed || LeftPressed || DownPressed || RightPressed))
    {
        car1.setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed, car2);
    }
    else
        car1.noMovementKeyPressed(); // Stop the car

    UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if ((UpPressed || LeftPressed || DownPressed || RightPressed))
    {
        car2.setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed, car1);
    }
    else
        car2.noMovementKeyPressed(); // Stop the car
    return 1;
}

void Game::loadObjectsRound()
{
    gameMode == 0 ? loadDuelRound() : loadTagRound();
}
