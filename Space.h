#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Space {
public:
    std::vector<sf::CircleShape> stars;
    const int maxStars = 800;
    float starSpeed = 0.01f;

    auto createStar(int const& x, int const& y, float const& r) -> void;

    Space();

    auto drawStars(sf::RenderWindow & window) -> void;
};


