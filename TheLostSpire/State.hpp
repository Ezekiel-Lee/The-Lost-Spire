#pragma once

#include <SFML/Graphics.hpp>

class StateMachine;

class State
{
public:
    virtual ~State() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt)                    = 0;
    virtual void render(sf::RenderWindow& window)    = 0;

    virtual void onEnter() {}
    virtual void onExit()  {}

    // true면 이 state가 아래 state를 가리지 않음 (예: 일시정지 오버레이)
    // StateMachine이 render할 때 이 state 아래까지 함께 그려줌
    virtual bool isOverlay() const { return false; }
};
