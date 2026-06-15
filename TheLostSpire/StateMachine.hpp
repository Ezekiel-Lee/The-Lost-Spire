#pragma once

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "State.hpp"

class StateMachine
{
public:
    void push(std::unique_ptr<State> state);
    void pop();
    void change(std::unique_ptr<State> state);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

    bool isEmpty() const { return m_states.empty(); }

private:
    std::stack<std::unique_ptr<State>> m_states;
};