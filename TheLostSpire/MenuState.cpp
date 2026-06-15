#include "MenuState.hpp"

MenuState::MenuState(StateMachine& sm, sf::RenderWindow& window)
    : m_stateMachine(sm)
    , m_window(window)
    , m_title(m_font)
    , m_prompt(m_font)
{
    m_title.setString("The Lost Spire");
    m_title.setCharacterSize(72);
    m_title.setFillColor(sf::Color(220, 180, 80));
    m_title.setPosition({400.f, 200.f});

    m_prompt.setString("Press ENTER to Begin");
    m_prompt.setCharacterSize(32);
    m_prompt.setFillColor(sf::Color(180, 180, 220));
    m_prompt.setPosition({450.f, 420.f});
}

void MenuState::handleEvent(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
        if (key->code == sf::Keyboard::Key::Enter)
            { /* TODO: GameState 전환 */ }
}

void MenuState::update(float dt) {}

void MenuState::render(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_prompt);
}