#pragma once

#include "GamePlayInfo.h"
#include <SFML/Graphics.hpp>


class GamePlay {
public:
    std::vector<sf::Text> texts;    // słowa które będą wyświetlane

    float currentSpeed;
    float originalSpeed;    // potrzebne do resetu (prędkość zmienia się podczas gry)
    float easySpeed = 0.1f;
    float mediumSpeed = 0.12f;
    float hardSpeed = 0.14f;
    int textSize;

    sf::Text textEntered;
    std::string strEntered;

    sf::Text highlighter;

    sf::Font font;

    sf::Font defaultFont;

    sf::Font textsFont;

    sf::Clock spawnClock;

    sf::RectangleShape exitButton;
    sf::Text exitButtonText;
    sf::Text exitButtonShortcut;


    explicit GamePlay(const sf::Font &defaultFont);

    void setFont(sf::Font const& font);

    void setTextSize(int const& textSize);

    void setCurrentSpeed(float speed);

    auto setUpEnteredText(sf::RenderWindow &window) -> void;

    auto addWordToTexts(GamePlayInfo const& gamePlayInfo, std::vector<std::string> const& randomStrs) -> void;

    auto moveTexts(float deltaTime) -> void;

    auto changeTextColors(sf::Window const& window) -> void;

    auto setUpExitButton() -> void;

    auto check(sf::RenderWindow & window, GamePlayInfo & gamePlayInfo, std::vector<std::string> const& randomStrs) -> void;

    auto drawTexts(sf::RenderWindow & window) -> void;

    auto changeTextSize(int const& val, sf::RenderWindow & window) -> void;

    auto changeFonts(sf::Font const& font) -> void ;

    auto reset() -> void ;

    auto drawButtons(sf::RenderWindow & window) -> void ;
};


