#include <SDL2/SDL.h>

#include "logger.hpp"
#include "sdl2base.hpp"

bool sdl2base::init(void)
{
    // Init logger
    logger::init();

    // Error for SDL2
    int sdlError = 0;

    // Init SDL with everything
    sdlError = SDL_Init(SDL_INIT_EVERYTHING);
    if(sdlError != 0)
    {
        logger::log("Error initializing SDL2: %s.", SDL_GetError());
        return false;
    }
    return true;
}

void sdl2base::exit(void)
{
    SDL_Quit();
}

void sdl2base::update(void)
{
    SDL_PumpEvents();
}