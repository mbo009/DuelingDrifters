#include "game.hpp"

/**
 * @brief Construct a new Game object
 *
 * @param window Pointer to the window
 * @param font Font inherited from menu
 * @param gameMode Game mode chosen by the player
 * @param pointLimit Point limit set by the player
 * @param timeLimit Time limit set by the player
 */
Game::Game(std::shared_ptr<sf::RenderWindow> &window, sf::Font &font, unsigned int gameMode, unsigned int pointLimit, sf::Time timeLimit) : window(window), font(font), gameMode(gameMode), pointLimit(pointLimit), timeLimit(timeLimit)
{
    // set available items
    itemTypes = {SpeedUp(), OpponentSlow(), Bomb(), Dash(), Reverse(), Stun(), Swap()};
    car1 = CarSprite("Blue", CAR1_START_POS.first, CAR1_START_POS.second, CAR_SCALE, 4);
    car2 = CarSprite("Red", CAR2_START_POS.first, CAR2_START_POS.second, CAR_SCALE, 8);
    loadAssets();
    resetCarsPosition();
    if (gameMode == 0)
    {
        totalPlayTime = sf::seconds(0);
    }
    if (gameMode == 1)
    {
        flag = Flag(FLAG_START_POS.first, FLAG_START_POS.second);
        flagHolder = 0;
        roundTimeLimit = sf::seconds(30);
        flag.setTexture(flag.getTexture());
        flag.setScale(FLAG_SCALE, FLAG_SCALE);
    }
    clock.restart();
    sinceLastItemSpawn.restart();
}

/**
 * @brief Load all assets
 *
 */
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

/**
 * @brief Load font from asset paths
 *
 */
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

/**
 * @brief Load map texture from asset paths
 *
 */
void Game::loadMap()
{
    // Load map
    mapTexture.loadFromFile(ASSET_PATHS_HPP::MAP_LIST[0]);
    map.setTexture(mapTexture, true);
    map.setScale(sf::Vector2f(MAP_SCALE, MAP_SCALE));
    map.setOrigin(190, 230); // Set origin to the center of the map
}

/**
 * @brief Load sound from asset paths (music, start sound, crash sound, victory sound)
 *
 */
void Game::loadSound()
{
    // Load game start sound
    startSoundBuffer.loadFromFile(ASSET_PATHS_HPP::GAMESTART_SFX);
    startSound.setBuffer(startSoundBuffer);
    startSound.setVolume(40);
    startSound.play();

    // Load music
    musicBuffer.loadFromFile(ASSET_PATHS_HPP::MUSIC_LIST[0]);
    music.setBuffer(musicBuffer);
    music.setLoop(true);
    music.setVolume(12);

    // Load crash sound
    crashSoundBuffer.loadFromFile(ASSET_PATHS_HPP::CRASH_SFX);
    crashSound.setBuffer(crashSoundBuffer);

    // Load victory sound
    victorySoundBuffer.loadFromFile(ASSET_PATHS_HPP::VICTORY_SFX);
    victorySound.setBuffer(victorySoundBuffer);
    victorySound.setVolume(50);

    // Play music
    music.play();
}

/**
 * @brief Reset cars position to the starting position
 *
 */
void Game::resetCarsPosition()
{
    car1.resetCar();
    car2.resetCar();
}

/**
 * @brief Announce the result and advance to the next round.
 * If one player reaches the point limit, call endGame() function.
 * @param winner index of the winner (0 for tie)
 */
void Game::nextRound(unsigned int winner)
{
    if (gameMode == 0 && (car1.getCarObj().getPoint() >= pointLimit || car2.getCarObj().getPoint() >= pointLimit))
    {
        endGame();
    }

    else
    {
        resetCarsPosition();
        startSound.play();
        car1PointsText.setString(std::to_string(car1.getCarObj().getPoint()));
        car2PointsText.setString(std::to_string(car2.getCarObj().getPoint()));
        countDown(winner);
    }
}

/**
 * @brief Spawn an item on the map by choosing random item type and random position.
 * Push this item to the vector of items on map.
 */
void Game::spawnItem()
{
    std::srand(std::time(nullptr));
    float xItemPos = BORDER_LEFT + 30 + (755 * std::rand() % static_cast<int>(BORDER_RIGHT - BORDER_LEFT - 60)); // Randomize item position
    float yItemPos = BORDER_TOP + 30 + (521 * std::rand() % static_cast<int>(BORDER_BOTTOM - BORDER_TOP - 60));  // Randomize item position
    sf::Clock itemClock = sf::Clock();

    itemsOnMap.push_back(
        {itemTypes[static_cast<int>(xItemPos) % static_cast<int>(yItemPos) % itemTypes.size()],
         itemClock});
    itemsOnMap[itemsOnMap.size() - 1].first.setPosition(xItemPos, yItemPos);

    itemsOnMap[itemsOnMap.size() - 1].first.setTexture(itemTypes[static_cast<int>(xItemPos) % static_cast<int>(yItemPos) % itemTypes.size()].getTexture());
}

/**
 * @brief Choose objects to draw on the screen.
 *
 * @param drawCar boolean to choose whether to draw cars
 * @param drawTimer boolean to choose whether to draw timer
 * @param drawPoints boolean to choose whether to draw points
 * @param drawFlag boolean to choose whether to draw flag
 * @param drawItems boolean to choose whether to draw items
 */
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

/**
 * @brief Check if there is a collision between two cars.
 *
 * @return true false
 */
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

/**
 * @brief Handle car collision by pushing the cars away from each other.
 * Calculate the dot product of the relative velocity and the relative position vectors to which car pushes the other.
 *
 */
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

    else
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

/**
 * @brief Handle events when car collides with an item.
 * Apply item effects to the car and remove the item from the map.
 */
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

/**
 * @brief Apply item effects to the car.
 *
 * @param car Car to apply item effects to
 * @param item Item to apply
 */
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

/**
 * @brief Check if car crossed the border of the map.
 *
 * @param car
 * @return unsigned int:
    0 - CAR DIDN'T CROSS LINE
    1 - UP / DOWN
    2 - LEFT / RIGHT
 */
unsigned int Game::carCrossedLine(const CarSprite &car)
{
    if (car.getY() < BORDER_TOP || car.getY() > BORDER_BOTTOM)
        return 1;
    if (car.getX() > BORDER_RIGHT || car.getX() < BORDER_LEFT)
        return 2;
    return 0;
    // return !(car.getX() > BORDER_LEFT && car.getY() > BORDER_TOP && car.getX() < BORDER_RIGHT && car.getY() < BORDER_BOTTOM);
}

/**
 * @brief Announce the winner of the round then count down to the next round.
 *
 * @param winner Previous round winner
 */
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

/**
 * @brief Print message on the screen.
 */
void Game::printMsg(const std::string &msg, float x, float y)
{
    message.setString(msg);
    message.setPosition(x, y);
    message.setFillColor(sf::Color::Black);
    window->draw(message);
    window->display();
    sf::sleep(sf::seconds(1));
}

/**
 * @brief End the game and display the winner.
 *
 */
void Game::endGame()
{
    music.stop();
    victorySound.play();
    view.setCenter(512, 512); // Set view to the center of the screen at point (512, 512)
    window->setView(view);
    unsigned int winner = ((car1.getPoints() < car2.getPoints()) ? 1 : (car1.getPoints() == car2.getPoints()) ? 0
                                                                                                              : 2);
    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(50);
    winnerText.setPosition(385, 135);

    car1.setScale(5, 5);
    car2.setScale(5, 5);

    if (winner > 0)
    {
        winnerText.setString(" Winner\n   is  \nPlayer " + std::to_string(winner));
        (winner - 1) ? car1.setPosition(430, 450) : car2.setPosition(430, 450);     // Final winner is in the middle
        (winner - 1) ? car2.setPosition(5000, 5000) : car1.setPosition(5000, 5000); // Final loser is out of the screen
        rotateCars(winnerText);
    }

    else if (winner == 0)
    {
        winnerText.setString("It's\n  a \n tie");
        car1.setPosition(200, 450); // Both are winners so draw side by side in the middle
        car2.setPosition(600, 450);
        rotateCars(winnerText);
    }

    gameEnded = 1;
}

/**
 * @brief Rotate cars 360 degrees and display the winner.
 *
 * @param textToDisplay Content of winner announcement
 */
void Game::rotateCars(sf::Text textToDisplay)
{
    for (int i = 0; i < 48; i++)
    {
        window->clear(sf::Color::Black);
        car1.rotateRight();
        car2.rotateRight();
        window->draw(car1);
        window->draw(car2);
        window->draw(textToDisplay);
        window->display();
        sf::sleep(sf::milliseconds(100));
    }
}

/**
 * @brief End round procedure for duel mode.
 *
 */
void Game::duelEndCondition()
{
    bool car1CrossedLine = carCrossedLine(car1) > 0;
    bool car2CrossedLine = carCrossedLine(car2) > 0;
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

/**
 * @brief Draw objects for duel mode and handle events.
 *
 */
void Game::loadDuelRound()
{
    sf::Time elapsed = clock.getElapsedTime() + totalPlayTime;
    if (elapsed.asSeconds() > timeLimit.asSeconds())
        endGame();
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

/**
 * @brief Check if car hit the wall and bounce it back to the map.
 *
 */
void Game::checkBounceCondition()
{
    // If car hit the wall, bounce it back to the map using getPushed function
    std::map<unsigned int, std::vector<float>> bounceDirectionMultipliers = {
        {1, {0, -1}},
        {2, {-1, 0}}};
    if (carCrossedLine(car1) > 0)
    {
        unsigned int situation = carCrossedLine(car1);
        car1.getPushed(car1.getVelocity().x * bounceDirectionMultipliers[situation][0], car1.getVelocity().y * bounceDirectionMultipliers[situation][1]);
    }

    if (carCrossedLine(car2))
    {
        unsigned int situation = carCrossedLine(car2);
        car2.getPushed(car2.getVelocity().x * bounceDirectionMultipliers[situation][0], car2.getVelocity().y * bounceDirectionMultipliers[situation][1]);
    }
}

/**
 * @brief Check if the flag is held by a car or steal the flag from the other car.
 *
 */
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

/**
 * @brief End round procedure for tag mode.
 *
 */
void Game::tagEndCondition()
{
    if (flagHolder == 1)
        car1.getCarObj().setPoint();

    else if (flagHolder == 2)
        car2.getCarObj().setPoint();

    if (clock.getElapsedTime().asSeconds() > timeLimit.asSeconds() ||
        car1.getPoints() >= pointLimit || car2.getPoints() >= pointLimit)
        endGame();
    else
    {
        nextRound(flagHolder);
        flagHolder = 0;
    }
    flag.setPosition(480, 470);
}

/**
 * @brief Draw objects for tag mode and handle events.
 *
 */
void Game::loadTagRound()
{
    sf::Time elapsed = clock.getElapsedTime();

    // calculate time left
    int min = static_cast<int>(roundTimeLimit.asSeconds() - elapsed.asSeconds()) / 60;
    int sec = static_cast<int>(roundTimeLimit.asSeconds() - elapsed.asSeconds()) % 60 + 1;
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

    // if cars collide, transfer the flag to other car
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

/**
 * @brief Handle events from the window. Get input (key pressed) from the player.
 *
 * @return int
 */
int Game::handleEvent()
{
    // Check if ESC key is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        gameEnded = 1;
        music.stop();
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

/**
 * @brief Draw objects and handle events base on game mode.
 *
 */
void Game::loadObjectsRound()
{
    gameMode == 0 ? loadDuelRound() : loadTagRound();
}

/**
 * @brief Check if the game is ended.
 *
 * @return true false
 */
bool Game::isEnded()
{
    return gameEnded;
}