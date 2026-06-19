#include "Collectible.hpp"
#include <cmath>

Collectible::Collectible(sf::Vector2f position)
    : m_shape(12.f)
    , m_baseY(position.y)
{
    m_shape.setFillColor(sf::Color(220, 180, 80)); // 금색 룬
    m_shape.setOutlineColor(sf::Color(255, 230, 150));
    m_shape.setOutlineThickness(2.f);
    m_shape.setPosition(position);
}

void Collectible::update(float dt)
{
    if (m_collected)
        return;

    m_floatTimer += dt;

    // sin 곡선으로 위아래 부유
    float offset = std::sin(m_floatTimer * 3.f) * 6.f;
    auto pos = m_shape.getPosition();
    m_shape.setPosition({pos.x, m_baseY + offset});
}

void Collectible::render(sf::RenderWindow& window)
{
    if (!m_collected)
        window.draw(m_shape);
}
