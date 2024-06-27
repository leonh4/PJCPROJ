#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "SettingsMenu.h"

class PostGameScreen {
public:
    sf::Text stats;

    sf::Font font;

    sf::RectangleShape backButton;
    sf::Text backText;
    sf::Text backShortcut;

    PostGameScreen(sf::Font const &font, sf::RenderWindow const &window, int const &killed,
                   float const &timePlayed);

    auto setUpBack(sf::RenderWindow const& window) -> void;

    auto drawPostGameScreen(sf::RenderWindow & window) const -> void;

    auto handlePostGameEvents(sf::RenderWindow & window,  MainMenu & mainMenu, GamePlayInfo &gamePlayInfo,
                              GamePlay &gamePlay, Generator &gen) -> void;

};



