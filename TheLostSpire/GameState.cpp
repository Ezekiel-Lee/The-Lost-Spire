#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

GameState::GameState(StateMachine& sm, sf::RenderWindow& window, int levelIndex)
    : m_stateMachine(sm)
    , m_window(window)
    , m_levelIndex(levelIndex)
    , m_scoreText(m_font)
    , m_levelText(m_font)
    , m_winText(m_font)
{
    m_allLevels = buildLevels();

    if (m_font.openFromFile("assets/fonts/static/Cinzel-Regular.ttf"))
    {
        m_scoreText.setCharacterSize(26);
        m_scoreText.setFillColor(sf::Color(220, 180, 80));
        m_scoreText.setPosition({20.f, 60.f});

        m_levelText.setCharacterSize(22);
        m_levelText.setFillColor(sf::Color(180, 180, 220));
        m_levelText.setPosition({20.f, 92.f});

        m_winText.setCharacterSize(48);
        m_winText.setFillColor(sf::Color(220, 180, 80));
        m_winText.setPosition({260.f, 300.f});
    }

    // 체력 하트 아이콘 — 한 번만 생성 (레벨 넘어가도 유지)
    for (int i = 0; i < m_player.health().getMax(); ++i)
    {
        sf::RectangleShape heart({24.f, 24.f});
        heart.setFillColor(sf::Color(200, 50, 70));
        heart.setPosition({20.f + i * 32.f, 20.f});
        m_heartIcons.push_back(heart);
    }

    loadLevel(m_levelIndex);
}

void GameState::loadLevel(int levelIndex)
{
    m_platforms.clear();
    m_collectibles.clear();
    m_enemies.clear();
    m_runesCollected  = 0;
    m_levelComplete   = false;
    m_transitionTimer = 0.f;

    const LevelData& lvl = m_allLevels[levelIndex];

    for (const auto& p : lvl.platforms)
    {
        sf::RectangleShape plat({p.w, p.h});
        plat.setFillColor(sf::Color(70, 55, 90));
        plat.setOutlineColor(sf::Color(140, 110, 180));
        plat.setOutlineThickness(2.f);
        plat.setPosition({p.x, p.y});
        m_platforms.push_back(plat);
    }

    for (const auto& r : lvl.runes)
        m_collectibles.emplace_back(sf::Vector2f{r.x, r.y});

    m_totalRunes = static_cast<int>(m_collectibles.size());

    for (const auto& e : lvl.enemies)
        m_enemies.emplace_back(sf::Vector2f{e.x, e.y}, e.patrolDistance);

    m_player.setPosition(lvl.playerSpawn);

    if (!m_font.getInfo().family.empty())
    {
        m_levelText.setString(
            "Level " + std::to_string(levelIndex + 1) + " / " +
            std::to_string(m_allLevels.size()) + " - " + lvl.name);

        m_winText.setString(
            levelIndex == static_cast<int>(m_allLevels.size()) - 1
                ? "Spire Reclaimed!"
                : "Level Complete!");
    }
}

void GameState::handleEvent(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Escape && !m_levelComplete)
        {
            m_stateMachine.push(std::make_unique<PauseState>(m_stateMachine, m_window));
            return;
        }
    }

    if (!m_levelComplete)
        m_player.handleEvent(event);
}

void GameState::update(float dt)
{
    // 레벨 클리어 후 잠깐 대기했다가 다음 레벨로 (또는 최종 클리어 처리)
    if (m_levelComplete)
    {
        m_transitionTimer += dt;

        if (m_transitionTimer >= TRANSITION_DELAY)
        {
            bool isLastLevel = (m_levelIndex == static_cast<int>(m_allLevels.size()) - 1);

            if (isLastLevel)
            {
                // 최종 레벨 클리어 — 잠시 더 보여주고 메뉴로 (여기서는 화면 유지)
                return;
            }

            m_levelIndex++;
            loadLevel(m_levelIndex);
        }
        return;
    }

    m_player.update(dt, m_platforms);

    for (auto& rune : m_collectibles)
        rune.update(dt);

    for (auto& enemy : m_enemies)
        enemy.update(dt, m_player.getPosition());

    checkRuneCollisions();
    checkEnemyCollisions();
    checkWinCondition();

    if (!m_font.getInfo().family.empty())
    {
        m_scoreText.setString(
            "Runes: " + std::to_string(m_runesCollected) + " / " + std::to_string(m_totalRunes));
    }

    if (m_player.health().isDead())
    {
        m_stateMachine.change(std::make_unique<GameOverState>(m_stateMachine, m_window));
    }
}

void GameState::checkRuneCollisions()
{
    sf::FloatRect playerBounds = m_player.getBounds();

    for (auto& rune : m_collectibles)
    {
        if (!rune.isCollected() && playerBounds.findIntersection(rune.getBounds()))
        {
            rune.collect();
            m_runesCollected++;
        }
    }
}

void GameState::checkEnemyCollisions()
{
    sf::FloatRect playerBounds = m_player.getBounds();

    for (auto& enemy : m_enemies)
    {
        if (!enemy.isAlive())
            continue;

        auto intersection = playerBounds.findIntersection(enemy.getBounds());
        if (!intersection.has_value())
            continue;

        bool  playerFalling = m_player.isFalling();
        float playerBottom  = playerBounds.position.y + playerBounds.size.y;
        float enemyTop      = enemy.getBounds().position.y;

        if (playerFalling && (playerBottom - enemyTop) < 22.f)
        {
            enemy.kill();
            m_player.bounceUp();
        }
        else
        {
            m_player.health().takeDamage(1);
        }
    }
}

void GameState::checkWinCondition()
{
    if (m_runesCollected >= m_totalRunes && !m_levelComplete)
    {
        m_levelComplete   = true;
        m_transitionTimer = 0.f;
    }
}

void GameState::drawHealthUI(sf::RenderWindow& window)
{
    int currentHealth = m_player.health().getCurrent();

    for (size_t i = 0; i < m_heartIcons.size(); ++i)
    {
        if (static_cast<int>(i) < currentHealth)
            m_heartIcons[i].setFillColor(sf::Color(200, 50, 70));
        else
            m_heartIcons[i].setFillColor(sf::Color(60, 60, 70));

        window.draw(m_heartIcons[i]);
    }
}

void GameState::render(sf::RenderWindow& window)
{
    for (const auto& platform : m_platforms)
        window.draw(platform);

    for (auto& rune : m_collectibles)
        rune.render(window);

    for (auto& enemy : m_enemies)
        enemy.render(window);

    m_player.render(window);

    drawHealthUI(window);

    if (!m_font.getInfo().family.empty())
    {
        window.draw(m_scoreText);
        window.draw(m_levelText);
    }

    if (m_levelComplete && !m_font.getInfo().family.empty())
        window.draw(m_winText);
}
