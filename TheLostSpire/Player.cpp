#include "Player.hpp"

Player::Player()
    : m_shape({40.f, 60.f})
    , m_velocity(0.f, 0.f)
{
    m_shape.setFillColor(sf::Color(255, 100, 100)); // 빨간색으로 변경
m_shape.setPosition({600.f, 300.f});
}

void Player::handleEvent(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Space ||
            key->code == sf::Keyboard::Key::Up    ||
            key->code == sf::Keyboard::Key::W)
        {
            m_jumpBufferTimer = JUMP_BUFFER;
        }
    }
}

void Player::update(float dt)
{
    if (m_coyoteTimer > 0.f)     m_coyoteTimer    -= dt;
    if (m_jumpBufferTimer > 0.f) m_jumpBufferTimer -= dt;

    float moveX = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        moveX = -MOVE_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        moveX = MOVE_SPEED;

    m_velocity.x = moveX;

    bool canJump = m_onGround || (m_coyoteTimer > 0.f && !m_coyoteUsed);
    if (m_jumpBufferTimer > 0.f && canJump)
    {
        m_velocity.y      = JUMP_FORCE;
        m_jumpBufferTimer = 0.f;
        m_coyoteUsed      = true;
        m_jumpCount       = 1;
    }
    else if (m_jumpBufferTimer > 0.f && m_jumpCount == 1 && !m_onGround)
    {
        m_velocity.y      = JUMP_FORCE * 0.85f;
        m_jumpBufferTimer = 0.f;
        m_jumpCount       = 2;
    }

    applyGravity(dt);
    m_shape.move(m_velocity * dt);
    checkGroundCollision();
}

void Player::applyGravity(float dt)
{
    if (!m_onGround)
        m_velocity.y += GRAVITY * dt;
}

void Player::checkGroundCollision()
{
    auto pos = m_shape.getPosition();

    if (pos.y + 60.f >= GROUND_Y)
    {
        m_shape.setPosition({pos.x, GROUND_Y - 60.f});
        m_velocity.y = 0.f;

        if (!m_onGround)
        {
            m_jumpCount  = 0;
            m_coyoteUsed = false;
        }

        m_onGround    = true;
        m_coyoteTimer = COYOTE_TIME;
    }
    else
    {
        if (m_onGround)
            m_coyoteTimer = COYOTE_TIME;

        m_onGround = false;
    }
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_shape);
}