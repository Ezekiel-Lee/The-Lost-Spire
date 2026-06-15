#include "states/StateMachine.hpp"

void StateMachine::push(std::unique_ptr<State> state)
{
    if (!m_states.empty())
        m_states.top()->onExit();

    m_states.push(std::move(state));
    m_states.top()->onEnter();
}

void StateMachine::pop()
{
    if (!m_states.empty())
    {
        m_states.top()->onExit();
        m_states.pop();
    }

    if (!m_states.empty())
        m_states.top()->onEnter();
}

void StateMachine::change(std::unique_ptr<State> state)
{
    pop();
    push(std::move(state));
}

void StateMachine::handleEvent(const sf::Event& event)
{
    if (!m_states.empty())
        m_states.top()->handleEvent(event);
}

void StateMachine::update(float dt)
{
    if (!m_states.empty())
        m_states.top()->update(dt);
}

void StateMachine::render(sf::RenderWindow& window)
{
    if (!m_states.empty())
        m_states.top()->render(window);
}
