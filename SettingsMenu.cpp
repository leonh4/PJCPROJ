#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(std::vector<sf::Font> const& fonts, sf::RenderWindow & window, GamePlay const& gamePlay)  {
    defaultFont = fonts[0];
    calibri = fonts[1];
    terminal = fonts[2];
    times = fonts[3];
    chooseDifficulty = sf::Text("Choose Difficulty: " , defaultFont, 50);
    chooseDifficulty.setFillColor(sf::Color::Green);
    chooseDifficulty.setPosition(50, 50);

    chooseTextSize = sf::Text("Choose Text Size: ", defaultFont, 50);
    chooseTextSize.setFillColor(sf::Color::Green);
    chooseTextSize.setPosition(50, 150);

    chooseFontText = sf::Text("Choose Font:", defaultFont, 50);
    chooseFontText.setFillColor(sf::Color::Green);
    chooseFontText.setPosition(50, 250);

    setUpEasyMode();
    setUpMediumMode();
    setUpHardMode();

    setUpBack(window);

    setUpSmallSizeButton();
    setUpMediumSizeButton();
    setUpLargeSizeButton();

    setUpArialButton();
    setUpTimesButton();
    setUpTerminalButton();
    setUpCalibiriButton();

    example = sf::Text("Example", defaultFont, gamePlay.textSize);
    example.setFillColor(sf::Color::Green);
    example.setPosition(
            window.getSize().x/2 - example.getLocalBounds().width,
            window.getSize().y/2 - example.getLocalBounds().height
            );
    exampleSpeed = gamePlay.currentSpeed;

    inSettings = false;
}

auto SettingsMenu::setUpEasyMode() -> void {
    easyModeButton = sf::RectangleShape(sf::Vector2f(200, 50));
    easyModeButton.setFillColor(sf::Color::Green);
    easyModeButton.setPosition(chooseDifficulty.getPosition().x + chooseDifficulty.getLocalBounds().width + 50, 58);

    easyModeButtonText = sf::Text("Easy", defaultFont, 40);
    easyModeButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = easyModeButton.getLocalBounds();
    auto textBounds = easyModeButtonText.getLocalBounds();
    easyModeButtonText.setPosition(
            easyModeButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            easyModeButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.3f
    );
}

auto SettingsMenu::setUpMediumMode() -> void {
    mediumModeButton = sf::RectangleShape(sf::Vector2f(200, 50));
    mediumModeButton.setFillColor(sf::Color::Red);
    mediumModeButton.setPosition(easyModeButton.getPosition().x + easyModeButton.getLocalBounds().width + 50, 58);

    mediumModeButtonText = sf::Text("Medium", defaultFont, 40);
    mediumModeButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = mediumModeButton.getLocalBounds();
    auto textBounds = mediumModeButtonText.getLocalBounds();
    mediumModeButtonText.setPosition(
            mediumModeButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            mediumModeButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.1f
    );
}

auto SettingsMenu::setUpHardMode() -> void {
    hardModeButton = sf::RectangleShape(sf::Vector2f(200, 50));
    hardModeButton.setFillColor(sf::Color::Green);
    hardModeButton.setPosition(mediumModeButton.getPosition().x + mediumModeButton.getLocalBounds().width + 50, 58);

    hardModeButtonText = sf::Text("Hard", defaultFont, 40);
    hardModeButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = hardModeButton.getLocalBounds();
    auto textBounds = hardModeButtonText.getLocalBounds();
    hardModeButtonText.setPosition(
            hardModeButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            hardModeButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.1f
    );
}

auto SettingsMenu::setUpBack(sf::RenderWindow & window) -> void {
    backButton = sf::RectangleShape(sf::Vector2f(300, 80));
    backButton.setFillColor(sf::Color::Green);
    backButton.setPosition(
            window.getSize().x/2 - backButton.getGlobalBounds().width/2,
            window.getSize().y - backButton.getLocalBounds().height*2
            );

    backButtonText = sf::Text("Back", defaultFont, 60);
    backButtonText.setFillColor(sf::Color::Black);
    auto buttonBounds = backButton.getLocalBounds();
    auto textBounds = backButtonText.getLocalBounds();
    backButtonText.setPosition(
            backButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            backButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.1f
    );

    backShortcut = sf::Text("CTRL-B", defaultFont, 15);
    backShortcut.setFillColor(sf::Color::Black);
    auto scBounds = backShortcut.getLocalBounds();
    backShortcut.setPosition(
            backButton.getPosition().x + backButton.getLocalBounds().width - scBounds.width,
            backButton.getPosition().y + backButton.getLocalBounds().height - scBounds.height*1.5f
    );
}

auto SettingsMenu::drawSettingsMenu(sf::RenderWindow &window)  -> void {
    // Sekcja poziom trudnosci
    window.draw(chooseDifficulty);

    window.draw(easyModeButton);
    window.draw(easyModeButtonText);

    window.draw(mediumModeButton);
    window.draw(mediumModeButtonText);

    window.draw(hardModeButton);
    window.draw(hardModeButtonText);

    window.draw(backButton);
    window.draw(backButtonText);
    window.draw(backShortcut);

    // Sekcja wielkości liter
    window.draw(chooseTextSize);

    window.draw(smallSizeButton);
    window.draw(smallSizeText);

    window.draw(mediumSizeButton);
    window.draw(mediumSizeText);

    window.draw(largeSizeButton);
    window.draw(largeSizeText);

    // Sekcja Font
    window.draw(chooseFontText);

    window.draw(arialButton);
    window.draw(arialText);

    window.draw(timesButton);
    window.draw(timesText);

    window.draw(terminalButton);
    window.draw(terminalText);

    window.draw(calibriButton);
    window.draw(calibriText);

    moveExample(window);
    window.draw(example);
}

auto SettingsMenu::handleSettingsEvents(sf::RenderWindow & window, GamePlay & gamePlay, GamePlayInfo & gamePlayInfo) -> void {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        auto mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed && inSettings) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (easyModeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    gamePlay.setCurrentSpeed(gamePlay.easySpeed);
                    gamePlay.originalSpeed = gamePlay.currentSpeed;     // orginal potzebny do restartów
                    gamePlayInfo.setDifficulty(hardModeButtonText.getString());     // pasek na górze podczas gry
                    easyModeButton.setFillColor(sf::Color::Red);    // radio button
                    mediumModeButton.setFillColor(sf::Color::Green);
                    hardModeButton.setFillColor(sf::Color::Green);
                    exampleSpeed = gamePlay.currentSpeed;   // przykładowe słowo porusz się zgodnie z trybem trudności
                } else if (mediumModeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    gamePlay.setCurrentSpeed(gamePlay.mediumSpeed);
                    gamePlay.originalSpeed = gamePlay.currentSpeed;
                    gamePlayInfo.setDifficulty(hardModeButtonText.getString());
                    easyModeButton.setFillColor(sf::Color::Green);
                    mediumModeButton.setFillColor(sf::Color::Red);
                    hardModeButton.setFillColor(sf::Color::Green);
                    exampleSpeed = gamePlay.currentSpeed;
                } else if (hardModeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                    gamePlay.setCurrentSpeed(gamePlay.hardSpeed);
                    gamePlay.originalSpeed = gamePlay.currentSpeed;
                    gamePlayInfo.setDifficulty(hardModeButtonText.getString());
                    easyModeButton.setFillColor(sf::Color::Green);
                    mediumModeButton.setFillColor(sf::Color::Green);
                    hardModeButton.setFillColor(sf::Color::Red);
                    exampleSpeed = gamePlay.currentSpeed;
                } else if (backButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    inSettings = false;     // wyjście z ustawnień
                } else if (smallSizeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeTextSize(30, window);    // zmiana wielkości słow które są dodawne na początku progarmu
                    gamePlay.setTextSize(30);
                    smallSizeButton.setFillColor(sf::Color::Red); // radio button
                    mediumSizeButton.setFillColor(sf::Color::Green);
                    largeSizeButton.setFillColor(sf::Color::Green);
                    example.setCharacterSize(30);   // przykładowe słowo zgodne z wybraną wielkością
                } else if (mediumSizeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeTextSize(40, window);
                    gamePlay.setTextSize(40);
                    smallSizeButton.setFillColor(sf::Color::Green);
                    mediumSizeButton.setFillColor(sf::Color::Red);
                    largeSizeButton.setFillColor(sf::Color::Green);
                    example.setCharacterSize(40);
                } else if (largeSizeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeTextSize(50, window);
                    gamePlay.setTextSize(50);
                    smallSizeButton.setFillColor(sf::Color::Green);
                    mediumSizeButton.setFillColor(sf::Color::Green);
                    largeSizeButton.setFillColor(sf::Color::Red);
                    example.setCharacterSize(50);
                } else if (arialButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeFonts(defaultFont);  // zmiana czionki słow które są dodawne na początku progarmu
                    gamePlay.setFont(defaultFont);
                    arialButton.setFillColor(sf::Color::Red); // radio button
                    calibriButton.setFillColor(sf::Color::Green);
                    terminalButton.setFillColor(sf::Color::Green);
                    timesButton.setFillColor(sf::Color::Green);
                    example.setFont(defaultFont);   // przykładowe słowo zgodne z wybraną czcionka
                } else if (calibriButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeFonts(calibri);
                    gamePlay.setFont(calibri);
                    arialButton.setFillColor(sf::Color::Green);
                    calibriButton.setFillColor(sf::Color::Red);
                    terminalButton.setFillColor(sf::Color::Green);
                    timesButton.setFillColor(sf::Color::Green);
                    example.setFont(calibri);
                } else if (terminalButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeFonts(terminal);
                    gamePlay.setFont(terminal);
                    arialButton.setFillColor(sf::Color::Green);
                    calibriButton.setFillColor(sf::Color::Green);
                    terminalButton.setFillColor(sf::Color::Red);
                    timesButton.setFillColor(sf::Color::Green);
                    example.setFont(terminal);
                } else if (timesButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                    gamePlay.changeFonts(times);
                    gamePlay.setFont(times);
                    arialButton.setFillColor(sf::Color::Green);
                    calibriButton.setFillColor(sf::Color::Green);
                    terminalButton.setFillColor(sf::Color::Green);
                    timesButton.setFillColor(sf::Color::Red);
                    example.setFont(times);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::B) && inSettings) {
            inSettings = false; // skrót klawiszowy
        }
    }
}

auto SettingsMenu::setUpSmallSizeButton() -> void {
    smallSizeButton = sf::RectangleShape(sf::Vector2f(200, 50));
    smallSizeButton.setFillColor(sf::Color::Green);
    smallSizeButton.setPosition(chooseDifficulty.getPosition().x + chooseDifficulty.getLocalBounds().width + 50, 158);

    smallSizeText = sf::Text("Small", defaultFont, 40);
    smallSizeText.setFillColor(sf::Color::Black);
    auto buttonBounds = smallSizeButton.getLocalBounds();
    auto textBounds = smallSizeText.getLocalBounds();
    smallSizeText.setPosition(
            smallSizeButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            smallSizeButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.1f
    );
}

auto SettingsMenu::setUpMediumSizeButton() -> void {
    mediumSizeButton = sf::RectangleShape(sf::Vector2f(200, 50));
    mediumSizeButton.setFillColor(sf::Color::Red);
    mediumSizeButton.setPosition(smallSizeButton.getPosition().x + smallSizeButton.getLocalBounds().width + 50, 158);

    mediumSizeText = sf::Text("Medium", defaultFont, 40);
    mediumSizeText.setFillColor(sf::Color::Black);
    auto buttonBounds = mediumSizeButton.getLocalBounds();
    auto textBounds = mediumSizeText.getLocalBounds();
    mediumSizeText.setPosition(
            mediumSizeButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            mediumSizeButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.2f
    );
}

auto SettingsMenu::setUpLargeSizeButton() -> void {
    largeSizeButton = sf::RectangleShape(sf::Vector2f(200, 50));
    largeSizeButton.setFillColor(sf::Color::Green);
    largeSizeButton.setPosition(mediumSizeButton.getPosition().x + mediumSizeButton.getLocalBounds().width + 50, 158);

    largeSizeText = sf::Text("Large", defaultFont, 40);
    largeSizeText.setFillColor(sf::Color::Black);
    auto buttonBounds = largeSizeButton.getLocalBounds();
    auto textBounds = largeSizeText.getLocalBounds();
    largeSizeText.setPosition(
            largeSizeButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            largeSizeButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.3f
    );
}

auto SettingsMenu::setUpArialButton() -> void {
    arialButton = sf::RectangleShape(sf::Vector2f(200, 50));
    arialButton.setFillColor(sf::Color::Red);
    arialButton.setPosition(chooseFontText.getPosition().x + chooseFontText.getLocalBounds().width + 50, 258);

    arialText = sf::Text("Arial", defaultFont, 40);
    arialText.setFillColor(sf::Color::Black);
    auto buttonBounds = arialButton.getLocalBounds();
    auto textBounds = arialText.getLocalBounds();
    arialText.setPosition(
            arialButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            arialButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.2f
    );
}

auto SettingsMenu::setUpTimesButton() -> void {
    timesButton = sf::RectangleShape(sf::Vector2f(200, 50));
    timesButton.setFillColor(sf::Color::Green);
    timesButton.setPosition(arialButton.getPosition().x + arialButton.getLocalBounds().width + 50, 258);

    timesText = sf::Text("Times", times, 40);
    timesText.setFillColor(sf::Color::Black);
    auto buttonBounds = timesButton.getLocalBounds();
    auto textBounds = timesText.getLocalBounds();
    timesText.setPosition(
            timesButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            timesButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.2f
    );
}

auto SettingsMenu::setUpTerminalButton() -> void {
    terminalButton = sf::RectangleShape(sf::Vector2f(200, 50));
    terminalButton.setFillColor(sf::Color::Green);
    terminalButton.setPosition(timesButton.getPosition().x + timesButton.getLocalBounds().width + 50, 258);

    terminalText = sf::Text("Terminal", terminal, 30);
    terminalText.setFillColor(sf::Color::Black);
    auto buttonBounds = terminalButton.getLocalBounds();
    auto textBounds = terminalText.getLocalBounds();
    terminalText.setPosition(
            terminalButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            terminalButton.getPosition().y + buttonBounds.height / 2 - textBounds.height / 1.5f
    );
}

auto SettingsMenu::setUpCalibiriButton() -> void {
    calibriButton = sf::RectangleShape(sf::Vector2f(200, 50));
    calibriButton.setFillColor(sf::Color::Green);
    calibriButton.setPosition(terminalButton.getPosition().x + terminalButton.getLocalBounds().width + 50, 258);

    calibriText = sf::Text("Calibri", calibri, 40);
    calibriText.setFillColor(sf::Color::Black);
    auto buttonBounds = calibriButton.getLocalBounds();
    auto textBounds = calibriText.getLocalBounds();
    calibriText.setPosition(
            calibriButton.getPosition().x + buttonBounds.width / 2 - textBounds.width / 2,
            calibriButton.getPosition().y + buttonBounds.height / 2 - textBounds.height
    );
}

auto SettingsMenu::moveExample(sf::RenderWindow const& window) -> void {    // poruszanie przykładowego słowa zgodnie z wybraną prędkością
    example.move(exampleSpeed, 0);
    if (example.getPosition().x + example.getLocalBounds().width > window.getSize().x) {
        example.setPosition(0, example.getPosition().y);
    }
}
