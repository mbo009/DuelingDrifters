#include "game.hpp"

std::vector<std::string> musicPath = {"battleTheme.ogg"};
std::vector<std::string> mapPath = {"spaceMap.png"};

Game::Game(std::shared_ptr<sf::RenderWindow> window) : window(window)
{
    window->setFramerateLimit(60);
    loadAssets();
    car1 = CarSprite("Red", 80, 50, 2.5);
    car2 = CarSprite("Red", 850, 850, 2.5);
    clock.restart();
}

void Game::loadAssets()
{
    // Set view
    view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
    // Load font
    font.loadFromFile(STATS_FONT_PATH);
    // Create text
    timerText = sf::Text("", font, STATS_FONT_SIZE);
    timerText.setPosition(TIMER_X, TIMER_Y);
    car1PointsText = sf::Text("", font, STATS_FONT_SIZE);
    car1PointsText.setPosition(CAR1_POINTS_X, CAR1_POINTS_Y);
    car2PointsText = sf::Text("", font, STATS_FONT_SIZE);
    car2PointsText.setPosition(CAR2_POINTS_X, CAR2_POINTS_Y);

    mapTexture.loadFromFile("img/" + mapPath[mapIndex]);
    map.setTexture(mapTexture, true);
    map.setScale(sf::Vector2f(1.5, 1.5));
    map.setOrigin(190, 230);

    loadMap();
    loadMusic();
    resetCarPosition();
}

// TODO: To change
void Game::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        window->close();

    bool UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    if ((UpPressed || LeftPressed || DownPressed || RightPressed))
    {
        car1.setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed);
        car1.updateDirectionTexture();
    }
    else
        car1.noMovementKeyPressed();

    UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if ((UpPressed || LeftPressed || DownPressed || RightPressed))
    {
        car2.setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed);
        car2.updateDirectionTexture();
    }
    else
        car2.noMovementKeyPressed();
}

void Game::nextSong()
{
    songIndex++;
    songIndex = songIndex % musicPath.size();
}

bool Game::carCrossedLine(const CarSprite &car)
{
    return !(car.getX() > BORDER_LEFT && car.getY() > BORDER_TOP && car.getX() < BORDER_RIGHT && car.getY() < BORDER_BOTTOM);
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

void Game::nextMap()
{
    mapIndex++;
    mapIndex = mapIndex % mapPath.size();
}

void Game::loadMusic()
{
    startSoundBuffer.loadFromFile("music/gameStart.ogg");
    startSound.setBuffer(startSoundBuffer);
    startSound.setVolume(60);
    startSound.play();

    musicBuffer.loadFromFile("music/" + musicPath[songIndex]); // to be changed
    music.setBuffer(musicBuffer);
    music.setLoop(true);
    music.setVolume(20);

    crashSoundBuffer.loadFromFile("music/crash.ogg");
    crashSound.setBuffer(crashSoundBuffer);
    crashSound.setVolume(60);

    music.play();
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

void Game::checkPointCondition()
{
    bool car1CrossedLine = carCrossedLine(car1);
    bool car2CrossedLine = carCrossedLine(car2);
    if (car1CrossedLine)
    {
        if (!car2CrossedLine)
            car2.getCarObj().scoredPoint();
        nextRound();
    }
    else if (car2CrossedLine)
    {
        car1.getCarObj().scoredPoint();
        nextRound();
    }
}

void Game::resetCarPosition()
{
    car1.restartPosition();
    car1.loadStartingPosition(1);
    car2.restartPosition();
    car2.loadStartingPosition(2);
}

void Game::nextRound()
{
    resetCarPosition();
    startSound.play();
    countDown();
}

void Game::drawObjects()
{
    window->draw(map);
    window->draw(timerText);
    window->draw(car1PointsText);
    window->draw(car2PointsText);
    window->draw(car1);
    window->draw(car2);
}
void Game::loadObjectsRound()
{
    sf::Time elapsed = clock.getElapsedTime();
    int min = static_cast<int>(elapsed.asSeconds()) / 60;
    int sec = static_cast<int>(elapsed.asSeconds()) % 60;
    timerText.setString((min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + ":" + (sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec)));
    car1PointsText.setString(std::to_string(car1.getCarObj().getPoints()));
    car2PointsText.setString(std::to_string(car2.getCarObj().getPoints()));
    car1.move();
    car2.move();
    checkPointCondition();
    if (car1.checkCollision(car2))
    {
        crashSound.play();
        handleCarCollision();
    }

    view.setCenter((car1.getX() + car2.getX() + 3090) / 8, (car1.getY() + car2.getY() + 3000) / 8);
    window->clear(sf::Color::Black);
    window->setView(view);
    drawObjects();
    window->display();
}