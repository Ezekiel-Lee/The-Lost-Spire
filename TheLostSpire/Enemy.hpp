#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    // 적의 행동 상태 — 순찰하다가 플레이어가 가까우면 추적
    enum class AIState { Patrol, Chase };

    Enemy(sf::Vector2f startPos, float patrolDistance);

    void update(float dt, sf::Vector2f playerPos);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

    bool isAlive() const { return m_alive; }
    void kill()          { m_alive = false; }

private:
    void updatePatrol(float dt);
    void updateChase(float dt, sf::Vector2f playerPos);

    sf::RectangleShape m_shape;
    AIState            m_state = AIState::Patrol;
    bool                m_alive = true;

    sf::Vector2f m_patrolStart;
    sf::Vector2f m_patrolEnd;
    int          m_patrolDir = 1; // 1 = 오른쪽, -1 = 왼쪽

    static constexpr float PATROL_SPEED      = 80.f;
    static constexpr float CHASE_SPEED       = 140.f;
    static constexpr float CHASE_RANGE       = 220.f; // 이 거리 안이면 추적 시작
    static constexpr float LOSE_CHASE_RANGE  = 320.f; // 이 거리 밖이면 추적 포기
};
