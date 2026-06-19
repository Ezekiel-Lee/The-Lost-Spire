#pragma once

#include <SFML/Graphics.hpp>

class Collectible
{
public:
    Collectible(sf::Vector2f position);

    void update(float dt);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

    bool isCollected() const { return m_collected; }
    void collect() { m_collected = true; }

private:
    sf::CircleShape m_shape;
    bool            m_collected = false;

    // 위아래로 살짝 떠다니는 효과
    float m_floatTimer = 0.f;
    float m_baseY      = 0.f;
};
