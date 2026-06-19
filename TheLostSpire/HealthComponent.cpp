#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int maxHealth)
    : m_max(maxHealth)
    , m_current(maxHealth)
{
}

void HealthComponent::takeDamage(int amount)
{
    if (isInvincible() || isDead())
        return;

    m_current -= amount;
    if (m_current < 0)
        m_current = 0;

    m_invincibleTimer = INVINCIBILITY_DURATION;
}

void HealthComponent::heal(int amount)
{
    m_current += amount;
    if (m_current > m_max)
        m_current = m_max;
}

void HealthComponent::reset()
{
    m_current = m_max;
    m_invincibleTimer = 0.f;
}

void HealthComponent::update(float dt)
{
    if (m_invincibleTimer > 0.f)
        m_invincibleTimer -= dt;
}
