#include "GameOverState.hpp"
#include "MenuState.hpp"

GameOverState::GameOverState(StateMachine& sm, sf::RenderWindow& window)
    : m_stateMachine(sm)
    , m_window(window)
    , m_gameOverText(m_font)
    , m_restartHint(m_font)
{
    if (m_font.openFromFile("assets/fonts/static/Cinzel-Regular.ttf"))
    {
        m_gameOverText.setString("The Spire Claims You");
        m_gameOverText.setCharacterSize(56);
        m_gameOverText.setFillColor(sf::Color(180, 60, 60));
        m_gameOverText.setPosition({230.f, 280.f});

        m_restartHint.setString("Press ENTER to Return to Menu");
        m_restartHint.setCharacterSize(28);
        m_restartHint.setFillColor(sf::Color(200, 200, 220));
        m_restartHint.setPosition({400.f, 400.f});
    }
}

void GameOverState::handleEvent(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Enter)
            m_stateMachine.change(std::make_unique<MenuState>(m_stateMachine, m_window));
    }
}

void GameOverState::update(float dt) {}

void GameOverState::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(10, 5, 20));

    if (!m_font.getInfo().family.empty())
    {
        window.draw(m_gameOverText);
        window.draw(m_restartHint);
    }
}
