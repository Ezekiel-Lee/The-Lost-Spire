#pragma once

class HealthComponent
{
public:
    explicit HealthComponent(int maxHealth = 3);

    void takeDamage(int amount = 1);
    void heal(int amount = 1);
    void reset();

    int  getCurrent() const { return m_current; }
    int  getMax()     const { return m_max; }
    bool isDead()     const { return m_current <= 0; }

    // 무적 시간 — 연속 데미지 방지
    void  update(float dt);
    bool  isInvincible() const { return m_invincibleTimer > 0.f; }

private:
    int   m_max;
    int   m_current;
    float m_invincibleTimer = 0.f;

    static constexpr float INVINCIBILITY_DURATION = 1.0f;
};
