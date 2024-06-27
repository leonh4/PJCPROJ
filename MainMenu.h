#pragma once

#include <SFML/Graphics.hpp>
#include "GamePlay.h"
#include "Generator.h"


class MainMenu {
public:
    sf::Font font;

    sf::Text text;

    sf::RectangleShape playButton;
    sf::Text playButtonText;
    sf::Text playShortcut;

    sf::RectangleShape settingsButton;
    sf::Text settingsButtonText;
    sf::Text settingsShortcut;

    sf::RectangleShape quitButton;
    sf::Text quitButtonText;
    sf::Text quitShortcut;

    bool gameStarted;

    MainMenu();

    auto setUpMainMenu(float wWidth, float wHeight) -> void;

    void setFont(const sf::Font &font);

    auto setUpPlayButton(float wWidth, float wHeight) -> void;

    auto setUpSettingsButton(float wWidth) -> void;

    auto setUpQuitButton(float wWidth) -> void;

    auto drawMenu(sf::RenderWindow & window) -> void;

    auto handleMainMenuEvents(sf::RenderWindow &window, bool &inSettings, GamePlayInfo & gamePlayInfo, GamePlay & gamePlay) -> void;

    auto startGame(GamePlayInfo & gamePlayInfo, GamePlay & gamePlay) -> void;

    auto restart(GamePlayInfo &gamePlayInfo, GamePlay &gamePlay, Generator &gen) -> void ;
};


