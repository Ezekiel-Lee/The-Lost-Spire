#include "MenuState.hpp"
#include "GameState.hpp"

MenuState::MenuState(StateMachine& sm, sf::RenderWindow& window)
    : m_stateMachine(sm)
    , m_window(window)
    , m_title(m_font)
    , m_prompt(m_font)
{
    // 폰트 로드 실패해도 크래시 안 나게
    bool fontLoaded = m_font.openFromFile("assets/fonts/static/Cinzel-Regular.ttf");

    if (fontLoaded)
    {
        m_title.setString("The Lost Spire");
        m_title.setCharacterSize(72);
        m_title.setFillColor(sf::Color(220, 180, 80));
        m_title.setPosition({300.f, 200.f});

        m_prompt.setString("Press ENTER to Begin");
        m_prompt.setCharacterSize(32);
        m_prompt.setFillColor(sf::Color(180, 180, 220));
        m_prompt.setPosition({400.f, 420.f});
    }
}

void MenuState::handleEvent(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
        if (key->code == sf::Keyboard::Key::Enter)
            m_stateMachine.change(std::make_unique<GameState>(m_stateMachine, m_window));
}

void MenuState::update(float dt) {}

void MenuState::render(sf::RenderWindow& window)
{
    // 폰트 없으면 ENTER 안내 도형으로 대체
    if (!m_font.getInfo().family.empty())
    {
        window.draw(m_title);
        window.draw(m_prompt);
    }
    else
    {
        // 폰트 없을 때 — 그냥 사각형으로 "Press ENTER" 암시
        sf::RectangleShape hint({300.f, 10.f});
        hint.setFillColor(sf::Color(180, 180, 220));
        hint.setPosition({490.f, 430.f});
        window.draw(hint);
    }
}