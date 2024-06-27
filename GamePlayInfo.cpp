#include "GamePlayInfo.h"

GamePlayInfo::GamePlayInfo(sf::RenderWindow &window) {
    topRec = sf::RectangleShape(sf::Vector2f(window.getSize().x, 50));
    topRec.setPosition(0, 0);
    topRec.setFillColor(sf::Color(105,105,105));
    lives = 10;
    difficulty = "Medium";
}

auto GamePlayInfo::updateStats() -> void {
    auto secsElapsed = static_cast<int>(timeFromStart.getElapsedTime().asSeconds());
    auto secs = secsElapsed % 60;
    auto mins = secsElapsed / 60;
    inGameStats.setString("Difficulty: " + difficulty +"\tLIVES: " + std::to_string(lives) +
    "\tKILLED: " + std::to_string(killed) +
    "\tTIME ELAPSED: " + std::to_string(mins) + "," + std::to_string(secs)
    );
}

auto GamePlayInfo::setUpInGameStats(sf::RenderWindow & window) -> void {
    inGameStats = sf::Text("Difficulty: " + difficulty +"\tLIVES: " + std::to_string(lives) +
            "\tKILLED: " + std::to_string(killed) +
            "\tTIME ELAPSED: " + std::to_string(timeFromStart.getElapsedTime().asSeconds())
            , font,
            30);

    inGameStats.setPosition(window.getSize().x/2 - inGameStats.getLocalBounds().width/2,   5);
}

auto GamePlayInfo::drawGamePlayInfo(sf::RenderWindow &window) -> void {
    window.draw(topRec);
    window.draw(inGameStats);
}

auto GamePlayInfo::calculateFinalTime() -> void {
        finalTime = timeFromStart.getElapsedTime().asSeconds();
}

void GamePlayInfo::setFont(const sf::Font &font1) {
    font = font1;
}

void GamePlayInfo::setDifficulty(const std::string &difficulty) {
    GamePlayInfo::difficulty = difficulty;
}

auto GamePlayInfo::reset() -> void {
    lives = 10;
    killed = 0;
    finalTime = 0.0f;
    timeFromStart.restart();
}
