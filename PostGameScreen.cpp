#include "PostGameScreen.h"

PostGameScreen::PostGameScreen(sf::Font const &font1, sf::RenderWindow const &window, int const &killed,float const &timePlayed) {
    font = font1;
    stats.setFont(font);
    auto secsPlayed = static_cast<int>(timePlayed) % 60;
    auto minsPlayed = static_cast<int>(timePlayed) / 60;
    auto secsPlayed2 = std::to_string(secsPlayed);
    if (secsPlayed < 10) {
        std::ranges::reverse(secsPlayed2);
        secsPlayed2 += "0";
        std::ranges::reverse(secsPlayed2);
    }
    stats.setString(
            "KILLED: " + std::to_string(killed) + "\nMINUTES PLAYED: " + std::to_string(minsPlayed) + ":" + secsPlayed2 +
            "\nWPM: " + std::to_string(killed / (timePlayed/60))
            );

    stats.setFillColor(sf::Color::Green);
    stats.setCharacterSize(70);
    stats.setPosition(window.getSize().x/2 - stats.getLocalBounds().width/2, window.getSize().y/15);

    setUpBack(window);
}

auto PostGameScreen::setUpBack(sf::RenderWindow const& window) -> void {
    backButton = sf::RectangleShape(sf::Vector2f(350, 90));
    backButton.setFillColor(sf::Color::Green);
    backButton.setPosition(
            window.getSize().x/2 - backButton.getLocalBounds().width/2,
            window.getSize().y - backButton.getLocalBounds().height*2
            );

    backText = sf::Text("Back", font, 60);
    backText.setFillColor(sf::Color::Black);
    auto buttonBounds = backButton.getLocalBounds();
    auto textBounds = backText.getLocalBounds();
    backText.setPosition(
            backButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            backButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.3f
    );

    backShortcut = sf::Text("CTRL-B", font, 15);
    backShortcut.setFillColor(sf::Color::Black);
    auto scBounds = backShortcut.getLocalBounds();
    backShortcut.setPosition(
            backButton.getPosition().x + backButton.getLocalBounds().width - scBounds.width,
            backButton.getPosition().y + backButton.getLocalBounds().height - scBounds.height*1.5f
    );
}

auto PostGameScreen::drawPostGameScreen(sf::RenderWindow &window) const -> void {
    window.draw(stats);

    window.draw(backButton);
    window.draw(backText);
    window.draw(backShortcut);
}

auto PostGameScreen::handlePostGameEvents(sf::RenderWindow & window,  MainMenu & mainMenu, GamePlayInfo &gamePlayInfo, GamePlay &gamePlay, Generator &gen) -> void {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        auto mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (backButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                mainMenu.restart(gamePlayInfo, gamePlay, gen);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            mainMenu.restart(gamePlayInfo, gamePlay, gen);
        }
    }
}





