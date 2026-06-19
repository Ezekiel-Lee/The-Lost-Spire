#include "GameState.hpp"

GameState::GameState(StateMachine& sm, sf::RenderWindow& window)
    : m_stateMachine(sm)
    , m_window(window)
    , m_ground({1280.f, 20.f})
{
    m_ground.setFillColor(sf::Color(60, 40, 20));
    m_ground.setPosition({0.f, 600.f});
}

void GameState::handleEvent(const sf::Event& event)
{
    m_player.handleEvent(event);
}

void GameState::update(float dt)
{
    m_player.update(dt);
}

void GameState::render(sf::RenderWindow& window)
{
    window.draw(m_ground);
    m_player.render(window);
}