#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "HealthComponent.hpp"

class Player
{
public:
    Player();

    void handleEvent(const sf::Event& event);
    void update(float dt, const std::vector<sf::RectangleShape>& platforms);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }
    void          setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }
    sf::Vector2f  getPosition() const { return m_shape.getPosition(); }

    // 적과의 상호작용
    bool isFalling() const { return m_velocity.y > 0.f; }
    void bounceUp()        { m_velocity.y = JUMP_FORCE * 0.6f; } // 적 밟았을 때 살짝 튕김

    HealthComponent& health() { return m_health; }

private:
    void applyGravity(float dt);
    void checkPlatformCollisions(const std::vector<sf::RectangleShape>& platforms);

    sf::RectangleShape m_shape;
    sf::Vector2f       m_velocity;
    HealthComponent    m_health{3};

    bool m_onGround  = false;
    int  m_jumpCount = 0;

    float m_coyoteTimer     = 0.f;
    bool  m_coyoteUsed      = false;
    float m_jumpBufferTimer = 0.f;

    static constexpr float GRAVITY     = 1800.f;
    static constexpr float JUMP_FORCE  = -650.f;
    static constexpr float MOVE_SPEED  = 300.f;
    static constexpr float COYOTE_TIME = 0.12f;
    static constexpr float JUMP_BUFFER = 0.1f;
};
