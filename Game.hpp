#pragma once

#include <SFML/Graphics.hpp>
#include "states/StateMachine.hpp"

class Game
{
public:
    Game();
    void run();

    static constexpr unsigned int WIDTH  = 1280;
    static constexpr unsigned int HEIGHT = 720;
    static constexpr float        FPS    = 60.f;

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow m_window;
    StateMachine     m_stateMachine;
};
