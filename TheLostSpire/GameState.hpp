#pragma once

#include "State.hpp"
#include "StateMachine.hpp"
#include "Player.hpp"
#include "Collectible.hpp"
#include "Enemy.hpp"
#include "LevelData.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class GameState : public State
{
public:
    // levelIndex: 0부터 시작 (레벨 1 = 0)
    GameState(StateMachine& sm, sf::RenderWindow& window, int levelIndex = 0);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    void loadLevel(int levelIndex);
    void checkRuneCollisions();
    void checkEnemyCollisions();
    void checkWinCondition();
    void drawHealthUI(sf::RenderWindow& window);

    StateMachine&     m_stateMachine;
    sf::RenderWindow& m_window;

    int m_levelIndex;
    std::vector<LevelData> m_allLevels;

    Player                          m_player;
    std::vector<sf::RectangleShape> m_platforms;
    std::vector<Collectible>        m_collectibles;
    std::vector<Enemy>              m_enemies;

    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Text m_winText;

    std::vector<sf::RectangleShape> m_heartIcons;

    int   m_runesCollected = 0;
    int   m_totalRunes     = 0;
    bool  m_levelComplete  = false;
    float m_transitionTimer = 0.f; // 레벨 클리어 후 다음 레벨로 넘어가기 전 대기

    static constexpr float TRANSITION_DELAY = 1.6f;
};
