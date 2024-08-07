#include "logger.hpp"
#include "graphics/window.hpp"

namespace
{
    SDL_Window *s_Window = NULL;
    int s_WindowWidth = 0;
    int s_WindowHeight = 0;
}

bool sdl::graphics::window::init(const char *windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    // Create window.
    s_Window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, windowFlags);
    if(s_Window == NULL)
    {
        logger::log("Error creating SDL2 window: %s.", SDL_GetError());
        return false;
    }
    // Save width and height.
    s_WindowWidth = windowWidth;
    s_WindowHeight = windowHeight;
    // Return true since it succeeded, we're here.
    return true;
}

void sdl::graphics::window::exit(void)
{
    if(s_Window != NULL)
    {
        SDL_DestroyWindow(s_Window);
    }
}

SDL_Window *sdl::graphics::window::getWindow(void)
{
    return s_Window;
}

int sdl::graphics::window::getWindowWidth(void)
{
    return s_WindowWidth;
}

int sdl::graphics::window::getWindowHeight(void)
{
    return s_WindowHeight;
}