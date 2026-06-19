#pragma once

#include "State.hpp"
#include "StateMachine.hpp"
#include <SFML/Graphics.hpp>

class PauseState : public State
{
public:
    PauseState(StateMachine& sm, sf::RenderWindow& window);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    bool isOverlay() const override { return true; }

private:
    StateMachine&     m_stateMachine;
    sf::RenderWindow& m_window;

    sf::RectangleShape m_overlay; // 반투명 어두운 배경
    sf::Font           m_font;
    sf::Text           m_pausedText;
    sf::Text           m_resumeHint;
};
