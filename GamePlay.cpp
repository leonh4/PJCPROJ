#include "GamePlay.h"


auto GamePlay::setUpEnteredText(sf::RenderWindow &window) -> void {
    textSize = 40;
    textEntered = sf::Text("12345678", font, textSize); // "12345678" żeby wpisywany tekst był na środku ekranu
    textEntered.setPosition(window.getSize().x/2 - textEntered.getLocalBounds().width/2, window.getSize().y - textEntered.getLocalBounds().height*1.7f);
    textEntered.setFillColor(sf::Color::Red);
    textEntered.setString(strEntered);

    highlighter = sf::Text("", font, textSize);
    highlighter.setFillColor(sf::Color::Transparent);
}

auto GamePlay::addWordToTexts(GamePlayInfo const& gamePlayInfo, std::vector<std::string> const& randomStrs) -> void {
    auto randomStr = randomStrs[rand() % randomStrs.size()];    // losowy string z wylosowanego pliku

    // przediał w którym mają pojawiać się słowa
    auto minY = gamePlayInfo.topRec.getLocalBounds().height;
    auto maxY = textEntered.getPosition().y - minY;

    auto textToAdd = sf::Text(randomStr, font, textSize);
    textToAdd.setFont(font);
    textToAdd.setCharacterSize(textSize);
    textToAdd.setPosition(-textToAdd.getLocalBounds().width, minY + static_cast<float>(rand() % static_cast<int>(maxY - minY)));

    auto overlapping = false;   // do sprawdzenia czy dodawne słowo nachodzi na wyświetlane słowa
    auto minDistanceY = 100.0f;
    auto minDistanceX = textToAdd.getLocalBounds().width + 20.f;

    auto same1stlLetter = false; // do sprawdzenia czy dodawne zaczyna się na tą samą litere co wyświetlane słowa

    for (auto const& text : texts) {
        // odległość słowa od wyświetlancyh
        auto distanceX = std::abs(text.getPosition().x - textToAdd.getPosition().x);
        auto distanceY = std::abs(text.getPosition().y - textToAdd.getPosition().y);

        if (distanceX < minDistanceX && distanceY < minDistanceY) {
            overlapping = true;
            break;      // nachodzi z którymś z wyśwetlancyh
        }

        if (textToAdd.getString()[0] == text.getString()[0]) {
            same1stlLetter = true;
            break;  // zaczyna się na to samo co już wyśwetlane słowo
        }
    }

    if (!overlapping && !same1stlLetter) {  // jeżeli spełnia wymagania nie nachodzenia i zaczynania się na inną lieterę dodaj do wyświetlanych
        textToAdd.setFillColor(sf::Color::Green);
        texts.push_back(textToAdd);
    }
}

void GamePlay::setFont(const sf::Font &font1) {
    font = font1;
}

void GamePlay::setTextSize(int const & textSize1) {
    textSize = textSize1;
}

auto GamePlay::moveTexts(float deltaTime) -> void {
    for (auto &text: texts) {
        text.move(currentSpeed * deltaTime, 0);
    }
}

void GamePlay::setCurrentSpeed(float speed) {
    currentSpeed = speed;
}

auto GamePlay::changeTextColors(const sf::Window &window) -> void {
    auto interval = window.getSize().x/3;
    for (auto & text : texts) {
        if (text.getPosition().x > interval && text.getPosition().x < interval*2) {
            text.setFillColor(sf::Color::Yellow);
        } else if (text.getPosition().x > interval*2) {
            text.setFillColor(sf::Color(255,120,0));
        }
    }
}

auto GamePlay::check(sf::RenderWindow &window, GamePlayInfo &gamePlayInfo, std::vector<std::string> const& randomStrs) -> void {
    auto highlight = false;     // czy ma podświetlać

    for (const auto& text : texts) {
        auto len = 0;   // ilość wspólnych znaków między wpisywanym słowem, a wyświetlanym

        for (int i = 0; i < std::min(text.getString().getSize(), strEntered.size()); ++i) {
            if (text.getString()[i] != strEntered[i]) {
                break;
            }
            len++;
        }

        if (len > 0) {  // ustawienie podświetlacza na wpisywane słowo
            highlighter.setString(text.getString().substring(0, len));
            highlighter.setPosition(text.getPosition());
            highlighter.setFillColor(sf::Color::Red);
            highlight = true;
            break;
        }
    }

    if (!highlight) {
        highlighter.setFillColor(sf::Color::Transparent);
    }

    for (auto textItr = texts.begin(); textItr != texts.end(); ++textItr) {
        if (textItr->getPosition().x > window.getSize().x) {    // słowo wyszło poza ekran
            textItr = texts.erase(textItr);
            gamePlayInfo.lives--;
            gamePlayInfo.colorChange.restart();    // do chwilowej zmiany tekstu na czerwono na górze
            gamePlayInfo.inGameStats.setFillColor(sf::Color::Red);  // _''_
        } else if (strEntered == textItr->getString()) {    // słowo zostało skasowane
            if (gamePlayInfo.killed % 10 == 0) currentSpeed += 0.01f;
            textItr = texts.erase(textItr);
            gamePlayInfo.killed++;
            strEntered.clear();
            textEntered.setString(strEntered);
            addWordToTexts(gamePlayInfo, randomStrs);
        }
    }
}


auto GamePlay::drawTexts(sf::RenderWindow &window) -> void {
    for (auto const& text : texts) {
        window.draw(text);
    }
    if (highlighter.getFillColor() != sf::Color::Transparent) {
        window.draw(highlighter);
    }
}

auto GamePlay::changeTextSize(const int &val, sf::RenderWindow & window) -> void { // używane przy zminie ustawień
    for (auto & text : texts) {
        text.setCharacterSize(val);
    }
    textEntered.setCharacterSize(val);
    textEntered.setString("12345678"); // żeby było na środku
    highlighter.setCharacterSize(val);
    textEntered.setPosition(window.getSize().x/2 - textEntered.getLocalBounds().width/2, window.getSize().y - textEntered.getLocalBounds().height*1.8f);
    textEntered.setString("");
}

auto GamePlay::changeFonts(const sf::Font &font) -> void { // używane przy zminie ustawień
    for (auto & text : texts) {
        text.setFont(font);
    }
    textEntered.setFont(font);
    highlighter.setFont(font);
}

auto GamePlay::reset() -> void { // granie po skończonej grze/po wyjściu z zaczętej
    strEntered.clear();
    textEntered.setString(strEntered);
    texts.clear();
    spawnClock.restart();
    currentSpeed = originalSpeed;
}


auto GamePlay::setUpExitButton() -> void {
    exitButton = sf::RectangleShape(sf::Vector2f(100, 50));
    exitButton.setFillColor(sf::Color::Green);
    exitButton.setPosition(0, 0);

    exitButtonText = sf::Text("Exit", defaultFont, 30);
    exitButtonText.setFillColor(sf::Color::Black);
    auto buttonPos = exitButton.getPosition();
    auto buttonSize = exitButton.getSize();
    auto textBounds = exitButtonText.getLocalBounds();
    exitButtonText.setPosition(
            buttonPos.x + (buttonSize.x - textBounds.width) / 2,
            buttonPos.y + (buttonSize.y - textBounds.height) / 2 - textBounds.top
    );

    exitButtonShortcut = sf::Text("CTRL-E", defaultFont, 10);
    exitButtonShortcut.setFillColor(sf::Color::Black);
    auto scBounds = exitButtonShortcut.getLocalBounds();
    exitButtonShortcut.setPosition(
            exitButton.getPosition().x + exitButton.getLocalBounds().width - scBounds.width,
            exitButton.getPosition().y + exitButton.getLocalBounds().height - scBounds.height*1.5f
    );
}

auto GamePlay::drawButtons(sf::RenderWindow &window) -> void {
    window.draw(exitButton);
    window.draw(exitButtonText);
    window.draw(exitButtonShortcut);
}

GamePlay::GamePlay(const sf::Font &defaultFont) : defaultFont(defaultFont) {
    currentSpeed = mediumSpeed;
    originalSpeed = currentSpeed;
    setUpExitButton();
}


