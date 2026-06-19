#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

private:
    void applyGravity(float dt);
    void checkGroundCollision();

    sf::RectangleShape m_shape;

    sf::Vector2f m_velocity;

    bool m_onGround      = false;
    bool m_canDoubleJump = false;
    int  m_jumpCount     = 0;

    // 코요테 타임 — 발판 끝에서도 점프 가능
    float m_coyoteTimer    = 0.f;
    bool  m_coyoteUsed     = false;

    // 점프 버퍼 — 착지 직전에 눌러도 점프
    float m_jumpBufferTimer = 0.f;

    static constexpr float GRAVITY       = 1800.f;
    static constexpr float JUMP_FORCE    = -650.f;
    static constexpr float MOVE_SPEED    = 300.f;
    static constexpr float COYOTE_TIME   = 0.12f;
    static constexpr float JUMP_BUFFER   = 0.1f;
    static constexpr float GROUND_Y      = 600.f; // 임시 바닥
};