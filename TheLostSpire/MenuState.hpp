#pragma once

#include "State.hpp"
#include "StateMachine.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public State
{
public:
    MenuState(StateMachine& sm, sf::RenderWindow& window);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine&     m_stateMachine;
    sf::RenderWindow& m_window;

    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_prompt;
};