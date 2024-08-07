#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "logger.hpp"
#include "sdllib.hpp"

bool sdl::init(void)
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

    // Just png for now, I guess
    sdlError = IMG_Init(IMG_INIT_PNG);
    if(sdlError != IMG_INIT_PNG)
    {
        logger::log("Error initializing SDL2_image for PNG: %s.", IMG_GetError());
        return false;
    }

    return true;
}

void sdl::exit(void)
{
    SDL_Quit();
}

void sdl::update(void)
{
    SDL_PumpEvents();
}