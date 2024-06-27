#include <SFML/Graphics.hpp>
#include "cmath"

class GamePlayInfo {
public:
    sf::RectangleShape topRec;
    sf::Text inGameStats;
    int killed = 0;
    int lives = 10;
    sf::Clock timeFromStart;
    float finalTime;
    sf::Font font;
    std::string difficulty;
    sf::Clock colorChange;

    explicit GamePlayInfo(sf::RenderWindow & window);

    void setFont(const sf::Font &font);

    auto updateStats() -> void;

   auto setUpInGameStats(sf::RenderWindow & window) -> void;

   auto drawGamePlayInfo(sf::RenderWindow & window) -> void;

   auto calculateFinalTime() -> void;

    void setDifficulty(const std::string &difficulty);

    auto reset() -> void ;
};


