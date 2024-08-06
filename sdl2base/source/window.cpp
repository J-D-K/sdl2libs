#include "logger.hpp"
#include "window.hpp"

namespace
{
    SDL_Window *s_Window = NULL;
}

SDL_Window *sdl2base::window::init(const char *windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    s_Window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, windowFlags);
    if(s_Window == NULL)
    {
        logger::log("Error creating SDL2 window: %s.", SDL_GetError());
        return NULL;
    }
    return s_Window;
}

void sdl2base::window::exit(void)
{
    if(s_Window != NULL)
    {
        SDL_DestroyWindow(s_Window);
    }
}