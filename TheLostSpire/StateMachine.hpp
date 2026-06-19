#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "State.hpp"

// State 스택 방식 — push/pop으로 메뉴<->게임<->일시정지 전환
// vector를 스택처럼 사용 (오버레이 렌더링을 위해 아래쪽도 순회 가능해야 함)
class StateMachine
{
public:
    void push(std::unique_ptr<State> state);
    void pop();
    void change(std::unique_ptr<State> state); // pop + push

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

    bool isEmpty() const { return m_states.empty(); }

private:
    std::vector<std::unique_ptr<State>> m_states;
};
