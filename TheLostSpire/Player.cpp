#include "Player.hpp"

Player::Player()
    : m_shape({40.f, 60.f})
    , m_velocity(0.f, 0.f)
{
    m_shape.setFillColor(sf::Color(255, 100, 100));
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

void Player::update(float dt, const std::vector<sf::RectangleShape>& platforms)
{
    m_health.update(dt);

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

    m_shape.move({m_velocity.x * dt, 0.f});
    m_shape.move({0.f, m_velocity.y * dt});

    checkPlatformCollisions(platforms);

    if (m_shape.getPosition().y > 800.f)
    {
        m_health.takeDamage(1);
        m_shape.setPosition({600.f, 100.f});
        m_velocity = {0.f, 0.f};
    }
}

void Player::applyGravity(float dt)
{
    if (!m_onGround)
        m_velocity.y += GRAVITY * dt;
}

void Player::checkPlatformCollisions(const std::vector<sf::RectangleShape>& platforms)
{
    bool wasOnGround = m_onGround;
    m_onGround = false;

    sf::FloatRect playerBounds = m_shape.getGlobalBounds();

    for (const auto& platform : platforms)
    {
        sf::FloatRect platBounds = platform.getGlobalBounds();

        if (playerBounds.findIntersection(platBounds))
        {
            float playerBottom = playerBounds.position.y + playerBounds.size.y;
            float platTop      = platBounds.position.y;

            if (m_velocity.y >= 0.f && playerBottom - platTop < 20.f)
            {
                m_shape.setPosition({m_shape.getPosition().x, platTop - playerBounds.size.y});
                m_velocity.y = 0.f;
                m_onGround   = true;
            }
        }
    }

    if (m_onGround && !wasOnGround)
    {
        m_jumpCount  = 0;
        m_coyoteUsed = false;
    }

    if (!m_onGround && wasOnGround)
    {
        m_coyoteTimer = COYOTE_TIME;
    }
}

void Player::render(sf::RenderWindow& window)
{
    // 무적 상태일 때 깜빡임 효과
    if (m_health.isInvincible())
    {
        int blink = static_cast<int>(m_health.getCurrent() * 1000) % 2;
        m_shape.setFillColor(blink ? sf::Color(255, 200, 200) : sf::Color(255, 100, 100));
    }
    else
    {
        m_shape.setFillColor(sf::Color(255, 100, 100));
    }

    window.draw(m_shape);
}
