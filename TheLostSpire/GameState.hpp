#pragma once

#include "State.hpp"
#include "StateMachine.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class GameState : public State
{
public:
    GameState(StateMachine& sm, sf::RenderWindow& window);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateMachine&     m_stateMachine;
    sf::RenderWindow& m_window;

    Player            m_player;

    // 임시 바닥
    sf::RectangleShape m_ground;
};