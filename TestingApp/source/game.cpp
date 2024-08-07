#include "game.hpp"
#include "sdllib.hpp"
#include "titlestate.hpp"

constexpr SDL_Color COLOR_BLACK = { 0x00, 0x00, 0x00, 0xFF };

game::game(const char *gameTitle, int windowWidth, int windowHeight)
{
    // To check whether or not stuff was initialized correctly.
    bool initialized = false;
    
    initialized = sdl::init();
    if(initialized == false)
    {
        return;
    }

    initialized = sdl::graphics::window::init(gameTitle, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
    if(initialized == false)
    {
        return;
    }

    initialized = sdl::graphics::renderer::init(sdl::graphics::window::getWindow(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(initialized == false)
    {
        return;
    }

    // Just hope this works
    sdl::input::init();

    // Push initial titlestate
    std::shared_ptr<gamestate> titlescreen = std::make_shared<titlestate>();
    game::m_StateStack.push(titlescreen);
    
    m_IsRunning = true;
}

game::~game()
{
    sdl::graphics::renderer::exit();
    sdl::graphics::window::exit();
    sdl::exit();
}

void game::update(void)
{
    sdl::update();
    sdl::input::update();

    if(sdl::input::keyPressed(SDL_SCANCODE_ESCAPE))
    {
        m_IsRunning = false;
    }

    if(m_StateStack.empty() == false)
    {
        m_StateStack.top()->update();
    }
}

void game::render(void)
{
    sdl::graphics::renderer::beginFrame(COLOR_BLACK);

    if(m_StateStack.empty() == false)
    {
        m_StateStack.top()->render();
    }

    sdl::graphics::renderer::endFrame();
}

bool game::isRunning(void)
{
    return m_IsRunning;
}
