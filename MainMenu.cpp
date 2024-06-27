#include "MainMenu.h"

auto MainMenu::setUpMainMenu(float wWidth, float wHeight) -> void {
    text = sf::Text("Monkey Type", font, 80);
    text.setFillColor(sf::Color::Green);
    text.setPosition(sf::Vector2f(wWidth/2 - text.getLocalBounds().width/2, wHeight/15));

    MainMenu::setUpPlayButton(wWidth, wHeight);

    MainMenu::setUpSettingsButton(wWidth);

    MainMenu::setUpQuitButton(wWidth);
}

auto MainMenu::setUpPlayButton(float wWidth, float wHeight) -> void {
    playButton = sf::RectangleShape(sf::Vector2f(text.getLocalBounds().width, 80));
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(sf::Vector2f(wWidth/2 - playButton.getLocalBounds().width/2, wHeight/4));

    playButtonText = sf::Text("Play", font, 60);
    playButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = playButton.getGlobalBounds();
    auto textBounds = playButtonText.getLocalBounds();
    playButtonText.setPosition(
            playButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            playButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.4f
    );

    playShortcut = sf::Text("CTRL-P", font, 15);
    playShortcut.setFillColor(sf::Color::Black);
    auto scBounds = playShortcut.getLocalBounds();
    playShortcut.setPosition(
            playButton.getPosition().x + buttonBounds.width - scBounds.width,
            playButton.getPosition().y + buttonBounds.height - scBounds.height*1.5f
    );
}

auto MainMenu::setUpSettingsButton(float wWidth) -> void {
    settingsButton = sf::RectangleShape(sf::Vector2f(text.getLocalBounds().width, 80));
    settingsButton.setFillColor(sf::Color::Green);
    settingsButton.setPosition(sf::Vector2f(wWidth/2 - settingsButton.getLocalBounds().width/2, playButton.getPosition().y + playButton.getLocalBounds().height * 1.5f));

    settingsButtonText = sf::Text("Settings", font, 60);
    settingsButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = settingsButton.getGlobalBounds();
    auto textBounds = settingsButtonText.getLocalBounds();
    settingsButtonText.setPosition(
            settingsButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            settingsButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.4f
    );

    settingsShortcut = sf::Text("CTRL-S", font, 15);
    settingsShortcut.setFillColor(sf::Color::Black);
    auto scBounds = playShortcut.getLocalBounds();
    settingsShortcut.setPosition(
            settingsButton.getPosition().x + buttonBounds.width - scBounds.width,
            settingsButton.getPosition().y + buttonBounds.height - scBounds.height*1.5f
    );
}


auto MainMenu::setUpQuitButton(float wWidth) -> void {
    quitButton = sf::RectangleShape(sf::Vector2f(text.getLocalBounds().width, 80));
    quitButton.setFillColor(sf::Color::Green);
    quitButton.setPosition(sf::Vector2f(wWidth/2 - quitButton.getLocalBounds().width/2, settingsButton.getPosition().y + settingsButton.getLocalBounds().height * 1.5f));

    quitButtonText = sf::Text("Quit", font, 60);
    quitButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = quitButton.getGlobalBounds();
    auto textBounds = quitButtonText.getLocalBounds();
    quitButtonText.setPosition(
            quitButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            quitButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.2f
    );

    quitShortcut = sf::Text("CTRL-Q", font, 15);
    quitShortcut.setFillColor(sf::Color::Black);
    auto scBounds = quitShortcut.getLocalBounds();
    quitShortcut.setPosition(
            quitButton.getPosition().x + buttonBounds.width - scBounds.width,
            quitButton.getPosition().y + buttonBounds.height - scBounds.height*1.5f
    );
}

auto MainMenu::drawMenu(sf::RenderWindow &window) -> void {
    window.draw(text);

    window.draw(playButton);
    window.draw(playButtonText);
    window.draw(playShortcut);

    window.draw(settingsButton);
    window.draw(settingsButtonText);
    window.draw(settingsShortcut);

    window.draw(quitButton);
    window.draw(quitButtonText);
    window.draw(quitShortcut);
}

void MainMenu::setFont(const sf::Font &font) {
    MainMenu::font = font;
}

MainMenu::MainMenu() {
    gameStarted = false;
}

auto MainMenu::handleMainMenuEvents(sf::RenderWindow &window, bool &inSettings, GamePlayInfo & gamePlayInfo, GamePlay & gamePlay) -> void {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        auto mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed && !gameStarted && !inSettings) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (playButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    startGame(gamePlayInfo, gamePlay);
                } else if (settingsButton.getGlobalBounds().contains(
                        {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    inSettings = true;
                } else if (quitButton.getGlobalBounds().contains(
                        {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    window.close();
                }

            }
        }
        // skróty klawiszowe:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
            !gameStarted && !inSettings) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::P) &&
            !gameStarted && !inSettings) {
            startGame(gamePlayInfo, gamePlay);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
            !gameStarted && !inSettings) { // przejście do ustawnień
            inSettings = true;
        }
    }
}

auto MainMenu::startGame(GamePlayInfo & gamePlayInfo, GamePlay & gamePlay) -> void {
    gameStarted = true;
    gamePlayInfo.timeFromStart.restart();
    gamePlay.spawnClock.restart();
}

auto MainMenu::restart(GamePlayInfo &gamePlayInfo, GamePlay &gamePlay, Generator &gen) -> void {
    gameStarted = false;
    gamePlayInfo.reset();
    gamePlay.reset();
    gen.wordsToDraw.clear();
    gen.initWordsToDraw(rand() % (gen.files.size() - 1));
    for (int i = 0; i < 5; ++i) { // na początku gry do nowa od razu są słowa
        gamePlay.addWordToTexts(gamePlayInfo, gen.wordsToDraw);
    }
}
