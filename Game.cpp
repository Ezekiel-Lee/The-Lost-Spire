#include "Game.hpp"
#include "states/MenuState.hpp"

Game::Game()
    : m_window(sf::VideoMode({WIDTH, HEIGHT}), "The Lost Spire")
{
    m_window.setFramerateLimit(static_cast<unsigned int>(FPS));
    m_stateMachine.push(std::make_unique<MenuState>(m_stateMachine, m_window));
}

void Game::run()
{
    sf::Clock clock;

    while (m_window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            m_window.close();

        m_stateMachine.handleEvent(*event);
    }
}

void Game::update(float dt)
{
    m_stateMachine.update(dt);
}

void Game::render()
{
    m_window.clear(sf::Color(10, 5, 20)); // 진한 판타지 배경색
    m_stateMachine.render(m_window);
    m_window.display();
}
