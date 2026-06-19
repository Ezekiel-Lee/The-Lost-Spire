#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f startPos, float patrolDistance)
    : m_shape({36.f, 36.f})
    , m_patrolStart(startPos)
    , m_patrolEnd({startPos.x + patrolDistance, startPos.y})
{
    m_shape.setFillColor(sf::Color(140, 40, 60));
    m_shape.setOutlineColor(sf::Color(220, 80, 100));
    m_shape.setOutlineThickness(2.f);
    m_shape.setPosition(startPos);
}

void Enemy::update(float dt, sf::Vector2f playerPos)
{
    if (!m_alive)
        return;

    sf::Vector2f myPos = m_shape.getPosition();
    float dx = playerPos.x - myPos.x;
    float dy = playerPos.y - myPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // 상태 전환 — 거리 기준 히스테리시스 (두 임계값으로 깜빡임 방지)
    if (m_state == AIState::Patrol && distance < CHASE_RANGE)
        m_state = AIState::Chase;
    else if (m_state == AIState::Chase && distance > LOSE_CHASE_RANGE)
        m_state = AIState::Patrol;

    if (m_state == AIState::Patrol)
        updatePatrol(dt);
    else
        updateChase(dt, playerPos);
}

void Enemy::updatePatrol(float dt)
{
    auto pos = m_shape.getPosition();
    pos.x += PATROL_SPEED * m_patrolDir * dt;

    if (pos.x >= m_patrolEnd.x)
    {
        pos.x = m_patrolEnd.x;
        m_patrolDir = -1;
    }
    else if (pos.x <= m_patrolStart.x)
    {
        pos.x = m_patrolStart.x;
        m_patrolDir = 1;
    }

    m_shape.setPosition(pos);
}

void Enemy::updateChase(float dt, sf::Vector2f playerPos)
{
    auto pos = m_shape.getPosition();
    float direction = (playerPos.x > pos.x) ? 1.f : -1.f;

    pos.x += CHASE_SPEED * direction * dt;
    m_shape.setPosition(pos);

    // 추적 중 색상 변화로 상태 시각화
    m_shape.setFillColor(sf::Color(200, 50, 50));
}

void Enemy::render(sf::RenderWindow& window)
{
    if (m_alive)
        window.draw(m_shape);
}
