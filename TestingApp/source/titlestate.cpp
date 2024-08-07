#include "titlestate.hpp"
#include "graphics/window.hpp"

constexpr int TITLE_FONT_SIZE = 256;

const char *GAME_TITLE = "SDL GAME";

constexpr SDL_Color COLOR_WHITE = { 0xFF, 0xFF, 0xFF, 0xFF };
constexpr SDL_Color COLOR_BLACK = { 0x00, 0x00, 0x00, 0xFF };

titlestate::titlestate(void)
{
    // Load font for title.
    m_TitleFont.load("titleFont.ttf");
    // Get width for centering and underscore.
    m_TitleTextWidth = m_TitleFont.getTextWidth(TITLE_FONT_SIZE, GAME_TITLE);
    // Get centered X for title
    m_TitleTextX = (sdl::graphics::window::getWindowWidth() / 2) - (m_TitleTextWidth / 2);
    // Start at center and go up according to TITLE_FONT_SIZE. 
    m_TitleTextY = (sdl::graphics::window::getWindowHeight() / 2) - (TITLE_FONT_SIZE + (TITLE_FONT_SIZE / 2));
}

titlestate::~titlestate() { }

void titlestate::update(void)
{

}

void titlestate::render(void)
{
    // Get window width and height first
    int windowWidth = sdl::graphics::window::getWindowWidth();
    int windowHeight = sdl::graphics::window::getWindowHeight();
    // Clear back to white cause it's classy
    sdl::graphics::renderer::renderRectangle(0, 0, windowWidth, windowHeight, COLOR_WHITE);
    // Render title text
    m_TitleFont.renderText(m_TitleTextX, m_TitleTextY, TITLE_FONT_SIZE, COLOR_BLACK, GAME_TITLE);
    // Render underline.
    sdl::graphics::renderer::renderRectangle(m_TitleTextX - 8, m_TitleTextY + TITLE_FONT_SIZE + 8, m_TitleTextWidth + 16, 4, COLOR_BLACK);
}