#include "PauseState.hpp"

PauseState::PauseState(StateMachine& sm, sf::RenderWindow& window)
    : m_stateMachine(sm)
    , m_window(window)
    , m_overlay({1280.f, 720.f})
    , m_pausedText(m_font)
    , m_resumeHint(m_font)
{
    m_overlay.setFillColor(sf::Color(0, 0, 0, 160)); // 반투명 검정

    if (m_font.openFromFile("assets/fonts/static/Cinzel-Regular.ttf"))
    {
        m_pausedText.setString("Paused");
        m_pausedText.setCharacterSize(64);
        m_pausedText.setFillColor(sf::Color(220, 180, 80));
        m_pausedText.setPosition({500.f, 280.f});

        m_resumeHint.setString("Press ESC to Resume");
        m_resumeHint.setCharacterSize(28);
        m_resumeHint.setFillColor(sf::Color(200, 200, 220));
        m_resumeHint.setPosition({470.f, 400.f});
    }
}

void PauseState::handleEvent(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Escape)
            m_stateMachine.pop(); // GameState로 복귀 — 상태가 보존됨
    }
}

void PauseState::update(float dt)
{
    // 일시정지 중에는 아무것도 업데이트 안 함 (그대로 멈춤)
}

void PauseState::render(sf::RenderWindow& window)
{
    // 주의: StateMachine은 최상단 state만 render하므로,
    // 아래 GameState 화면이 이미 그려진 상태에 오버레이만 덧그림
    window.draw(m_overlay);

    if (!m_font.getInfo().family.empty())
    {
        window.draw(m_pausedText);
        window.draw(m_resumeHint);
    }
}
