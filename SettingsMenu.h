#pragma once

#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include "GamePlay.h"

class SettingsMenu {
public:
    sf::Font defaultFont;
    sf::Font calibri;
    sf::Font terminal;
    sf::Font times;

    sf::Text chooseDifficulty;

    sf::RectangleShape easyModeButton;
    sf::Text easyModeButtonText;

    sf::RectangleShape mediumModeButton;
    sf::Text mediumModeButtonText;

    sf::RectangleShape hardModeButton;
    sf::Text hardModeButtonText;

    sf::RectangleShape backButton;
    sf::Text backButtonText;
    sf::Text backShortcut;

    sf::Text chooseTextSize;

    sf::RectangleShape smallSizeButton;
    sf::Text smallSizeText;

    sf::RectangleShape mediumSizeButton;
    sf::Text mediumSizeText;

    sf::RectangleShape largeSizeButton;
    sf::Text largeSizeText;

    sf::Text chooseFontText;

    sf::RectangleShape arialButton;
    sf::Text arialText;

    sf::RectangleShape timesButton;
    sf::Text timesText;

    sf::RectangleShape terminalButton;
    sf::Text terminalText;

    sf::RectangleShape calibriButton;
    sf::Text calibriText;

    sf::Text example;
    float exampleSpeed;

    bool inSettings;

    explicit SettingsMenu(std::vector<sf::Font> const& fonts, sf::RenderWindow & window,  GamePlay const& gamePlay);

    auto setUpEasyMode() -> void ;

    auto setUpMediumMode() -> void;

    auto setUpHardMode() -> void;

    auto setUpBack(sf::RenderWindow & window) -> void ;

    auto setUpSmallSizeButton() -> void ;

    auto setUpMediumSizeButton() -> void ;

    auto setUpLargeSizeButton() -> void ;

    auto setUpArialButton() -> void;

    auto setUpTimesButton() -> void;

    auto setUpTerminalButton() -> void ;

    auto setUpCalibiriButton() -> void;

    auto drawSettingsMenu(sf::RenderWindow & window)  -> void ;

    auto handleSettingsEvents(sf::RenderWindow & window, GamePlay & gamePlay, GamePlayInfo & gamePlayInfo) -> void;

    auto moveExample(sf::RenderWindow const& window) -> void;
};



