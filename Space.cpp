#include "Space.h"

auto Space::createStar(int const& x, int const& y, float const& r) -> void  {
    auto s = sf::CircleShape(r);
    s.setPosition(static_cast<float>(x), static_cast<float>(y));
    stars.push_back(s);
}

Space::Space() {}

auto Space::drawStars(sf::RenderWindow &window) -> void {
        for (sf::CircleShape &s: stars) {
            if (s.getPosition().x >= window.getSize().x) {
                s.setPosition(0.f, static_cast<float>(s.getPosition().y));
            }
            s.move(starSpeed, 0);
            window.draw(s);
        }
}
