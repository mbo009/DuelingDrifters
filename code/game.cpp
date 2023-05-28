#include "game.hpp"

Game::Game(std::shared_ptr<sf::RenderWindow> &window, sf::Font &font) : window(window), font(font)
{
    // set available items
    itemTypes = {SpeedUp(), OpponentSlow(), Bomb(), Dash(), Reverse(), Stun(), Swap()};

    car1 = CarSprite("Blue", 80, 50, 2.5, 4);
    car2 = CarSprite("Red", 850, 850, 2.5, 8);
    loadAssets();
    resetCarsPosition();
    clock.restart();
    sinceLastItemSpawn.restart();
}

void Game::spawnItem()
{
    // TODO: not spawn on player or other item
    std::srand(std::time(nullptr));
    float xItemPos = BORDER_LEFT + 30 + (755 * std::rand() % static_cast<int>(BORDER_RIGHT - BORDER_LEFT - 60));
    float yItemPos = BORDER_TOP + 30 + (521 * std::rand() % static_cast<int>(BORDER_BOTTOM - BORDER_TOP - 60));
    sf::Clock itemClock = sf::Clock();

    itemsOnMap.push_back(
        {
            itemTypes[static_cast<int>(xItemPos) % static_cast<int>(yItemPos) % itemTypes.size()],
            itemClock
        }
            );
    itemsOnMap[itemsOnMap.size() - 1].first.setPosition(xItemPos, yItemPos);

    // this somehow prevents error when copying texture
    itemsOnMap[itemsOnMap.size() - 1].first.setTexture(itemTypes[static_cast<int>(xItemPos) % static_cast<int>(yItemPos) % itemTypes.size()].getTexture());
}

void Game::loadAssets()
{
    // Set view
    view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
    loadFont();
    loadMap();
    loadMusic();
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
}

void Game::loadMap()
{
    // Load map
    mapTexture.loadFromFile(ASSET_PATHS_HPP::MAP_LIST[mapIndex]);
    map.setTexture(mapTexture, true);
    map.setScale(sf::Vector2f(MAP_SCALE, MAP_SCALE));
    map.setOrigin(190, 230);
}

void Game::nextMap()
{
    mapIndex++;
    mapIndex = mapIndex % ASSET_PATHS_HPP::MAP_LIST.size();
}

void Game::loadMusic()
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

void Game::nextMusic()
{
    musicIndex++;
    musicIndex = musicIndex % ASSET_PATHS_HPP::MUSIC_LIST.size();
}

void Game::drawObjects()
{
    window->draw(map);
    window->draw(timerText);
    window->draw(car1PointsText);
    window->draw(car2PointsText);
    window->draw(car1);
    window->draw(car2);
    for (auto &item : itemsOnMap)
        window->draw(item.first);
}

void Game::loadObjectsRound()
{
    sf::Time elapsed = clock.getElapsedTime() - roundTimeToSubtract;
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
    checkPointCondition();

    view.setCenter((car1.getX() + car2.getX() + 3090) / 8, (car1.getY() + car2.getY() + 3000) / 8);
    window->clear(sf::Color::Black);
    window->setView(view);
    drawObjects();
    window->display();
}

void Game::handleEvent()
{
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
}

void Game::checkCarCollisions()
{
    if (car1.checkCollision(car2))
    {
        crashSound.play();
        handleCarCollision();
    }
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

void Game::countDown()
{
    sf::Text countDownText;
    countDownText.setCharacterSize(300);
    countDownText.setFont(font);
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
        window->display();
        crashSound.play();
        sf::sleep(sf::milliseconds(500));
    }
    crashSound.setPitch(1);
}

bool Game::carCrossedLine(const CarSprite &car)
{
    return !(car.getX() > BORDER_LEFT && car.getY() > BORDER_TOP && car.getX() < BORDER_RIGHT && car.getY() < BORDER_BOTTOM);
}

void Game::checkPointCondition()
{
    bool car1CrossedLine = carCrossedLine(car1);
    bool car2CrossedLine = carCrossedLine(car2);
    if (car1CrossedLine)
    {
        if (!car2CrossedLine)
            car2.getCarObj().setPoint();
        nextRound();
        roundTimeToSubtract += sf::milliseconds(1500);
    }
    else if (car2CrossedLine)
    {
        car1.getCarObj().setPoint();
        nextRound();
        roundTimeToSubtract += sf::milliseconds(1500);
    }
}

void Game::resetCarsPosition()
{
    car1.resetCar();
    car2.resetCar();
}

void Game::nextRound()
{
    resetCarsPosition();
    startSound.play();
    car1PointsText.setString(std::to_string(car1.getCarObj().getPoint()));
    car2PointsText.setString(std::to_string(car2.getCarObj().getPoint()));
    countDown();
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