#include "MainMenu.h"
#include "SettingsMenu.h"
#include "PostGameScreen.h"
#include "GamePlay.h"
#include "Space.h"
#include "Generator.h"
#include <ctime>
#include <SFML/Graphics.hpp>
#include <vector>

auto randOne(int max) -> int {
    return rand() % (max + 1);
}


int main() {
    srand(static_cast<unsigned>(time(NULL)));

    auto window = sf::RenderWindow(
            sf::VideoMode({1600, 900}), "Monkey Type",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );

    auto defaultFont = sf::Font();
    if (!defaultFont.loadFromFile("../assets/arial.ttf")) {
        return EXIT_FAILURE;
    }

    auto calibriFont = sf::Font();
    if (!calibriFont.loadFromFile("../assets/calibri.ttf")) {
        return EXIT_FAILURE;
    }

    auto terminalFont = sf::Font();
    if (!terminalFont.loadFromFile("../assets/terminal.ttf")) {
        return EXIT_FAILURE;
    }

    auto timesFont = sf::Font();
    if (!timesFont.loadFromFile("../assets/times.ttf")) {
        return EXIT_FAILURE;
    }

    auto fonts = std::vector<sf::Font>{defaultFont, calibriFont, terminalFont, timesFont};

    auto mainMenu = MainMenu();
    mainMenu.setFont(defaultFont);
    mainMenu.setUpMainMenu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    auto gamePlayInfo = GamePlayInfo(window);
    gamePlayInfo.setFont(defaultFont);
    gamePlayInfo.setUpInGameStats( window);

    auto gamePlay = GamePlay(defaultFont);
    gamePlay.setFont(defaultFont);
    gamePlay.setUpEnteredText(window);

    auto settings = SettingsMenu(fonts, window, gamePlay);

   auto gen = Generator();
   gen.initWordsToDraw(randOne(gen.files.size() - 1));

    for (int i = 0; i < 5; ++i) { // na początku gry od razu są słowa
        gamePlay.addWordToTexts(gamePlayInfo, gen.wordsToDraw);
    }

    auto backgrd = Space(); // gwiazdy w tle

    while (backgrd.stars.size() < backgrd.maxStars) {
        backgrd.createStar(randOne(window.getSize().x), randOne(window.getSize().y), static_cast<float>(randOne(10))/7);
    }

    while (window.isOpen()) {
        if (!mainMenu.gameStarted && !settings.inSettings) {    // przyciski w main menu
            mainMenu.handleMainMenuEvents(window, settings.inSettings, gamePlayInfo, gamePlay);
        } else if (!mainMenu.gameStarted && settings.inSettings) {      // przyciski w ustawieniach
            settings.handleSettingsEvents(window, gamePlay, gamePlayInfo);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered && mainMenu.gameStarted) {
                // 8=Backspace, 32=space, <a,z>=<97,122>
                // https://pl.wikipedia.org/wiki/ASCII
                if ((event.text.unicode >= 97 && event.text.unicode <= 122) ||              // alfabet łaciński (lower case)
                    event.text.unicode == 8 || event.text.unicode == 32) {                  // Backspace i space
                    if (event.text.unicode == 32 && !gamePlay.strEntered.empty()) {         // Space
                        gamePlay.strEntered.clear();                                        // usuwa cały wpisany tekst
                    } else if (event.text.unicode == 8 && !gamePlay.strEntered.empty()) {   // Backspace
                        gamePlay.strEntered.pop_back();                                     // usuwa ostatni wpisany znak
                    } else if (event.text.unicode != 8 && event.text.unicode != 32) {       // a-z
                        gamePlay.strEntered += static_cast<char>(event.text.unicode);       // dodaje wpisaną literke
                    }
                    gamePlay.textEntered.setString(gamePlay.strEntered);
                }
            }
            auto mousePos = sf::Mouse::getPosition(window);
            // opuszczenie gry poprzez przycisk
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gamePlay.exitButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        mainMenu.restart(gamePlayInfo, gamePlay, gen);
                    }
                }
            }
            // opuszczenie gry poprzez skrót klawiszowy
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&mainMenu.gameStarted) {
                mainMenu.restart(gamePlayInfo, gamePlay, gen);
            }
        }
        window.clear();

        backgrd.drawStars(window);
        if (mainMenu.gameStarted) {
            if (gamePlayInfo.lives > 0) {
                if (gamePlay.spawnClock.getElapsedTime().asSeconds() >= 1.f) {  // co sekunde nowe słowo
                    gamePlay.addWordToTexts(gamePlayInfo, gen.wordsToDraw);
                    gamePlay.spawnClock.restart();
                }

                gamePlay.moveTexts();
                gamePlay.drawTexts(window);
                gamePlay.changeTextColors(window);

                gamePlay.check(window, gamePlayInfo, gen.wordsToDraw);  // sprawdz czy trzeba usunąc słowo/podświetlić

                if (gamePlayInfo.colorChange.getElapsedTime().asSeconds() > 0.1) gamePlayInfo.inGameStats.setFillColor(sf::Color::White);

                gamePlayInfo.updateStats();

                window.draw(gamePlay.textEntered);

                gamePlayInfo.drawGamePlayInfo(window);
                gamePlay.drawButtons(window);
                gamePlayInfo.calculateFinalTime();  // potrzebne do koncowych statystyk
            } else {
                window.clear();

                backgrd.drawStars(window);
                auto postGameScreen = PostGameScreen(defaultFont, window, gamePlayInfo.killed, gamePlayInfo.finalTime);
                postGameScreen.handlePostGameEvents(window,mainMenu, gamePlayInfo, gamePlay, gen);  // powrót do main menu po grze
                postGameScreen.drawPostGameScreen(window);
            }
        }
        if (!mainMenu.gameStarted && settings.inSettings) settings.drawSettingsMenu(window);
        if (!mainMenu.gameStarted && !settings.inSettings) mainMenu.drawMenu(window);
        window.display();
    }
}
