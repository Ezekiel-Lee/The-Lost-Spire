#include "StateMachine.hpp"

void StateMachine::push(std::unique_ptr<State> state)
{
    if (!m_states.empty())
        m_states.back()->onExit();

    m_states.push_back(std::move(state));
    m_states.back()->onEnter();
}

void StateMachine::pop()
{
    if (!m_states.empty())
    {
        m_states.back()->onExit();
        m_states.pop_back();
    }

    if (!m_states.empty())
        m_states.back()->onEnter();
}

void StateMachine::change(std::unique_ptr<State> state)
{
    pop();
    push(std::move(state));
}

void StateMachine::handleEvent(const sf::Event& event)
{
    if (!m_states.empty())
        m_states.back()->handleEvent(event);
}

void StateMachine::update(float dt)
{
    if (!m_states.empty())
        m_states.back()->update(dt);
}

void StateMachine::render(sf::RenderWindow& window)
{
    if (m_states.empty())
        return;

    // 오버레이가 아닌 가장 가까운 state부터 그리기 시작점 찾기
    size_t startIdx = m_states.size() - 1;
    while (startIdx > 0 && m_states[startIdx]->isOverlay())
        --startIdx;

    for (size_t i = startIdx; i < m_states.size(); ++i)
        m_states[i]->render(window);
}
