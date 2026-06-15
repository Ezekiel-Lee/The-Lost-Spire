#include "states/MenuState.hpp"
#include <SFML/Window/Keyboard.hpp>

MenuState::MenuState(StateMachine& sm, sf::RenderWindow& window)
    : m_stateMachine(sm)
    , m_window(window)
    , m_title(m_font)
    , m_prompt(m_font)
{
    // 폰트는 assets/fonts/ 에 넣어두세요
    // 무료 판타지 폰트 추천: "MedievalSharp" or "Cinzel" (Google Fonts)
    if (!m_font.openFromFile("assets/fonts/Cinzel-Regular.ttf"))
    {
        // 폴백: 기본 렌더링 (폰트 없어도 크래시 방지)
    }

    m_title.setString("The Lost Spire");
    m_title.setCharacterSize(72);
    m_title.setFillColor(sf::Color(220, 180, 80)); // 금색
    m_title.setPosition({640.f - m_title.getGlobalBounds().size.x / 2.f, 200.f});

    m_prompt.setString("Press ENTER to Begin");
    m_prompt.setCharacterSize(32);
    m_prompt.setFillColor(sf::Color(180, 180, 220));
    m_prompt.setPosition({640.f - m_prompt.getGlobalBounds().size.x / 2.f, 420.f});
}

void MenuState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Enter)
        {
            // TODO: m_stateMachine.change(std::make_unique<GameState>(...));
        }
    }
}

void MenuState::update(float dt)
{
    // 나중에 타이틀 페이드인 / 파티클 추가
}

void MenuState::render(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_prompt);
}
