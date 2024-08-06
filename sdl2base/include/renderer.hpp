#pragma once
#include <SDL2/SDL.h>

namespace sdl2base
{
    namespace renderer
    {
        // Creates render
        SDL_Renderer *init(SDL_Window *window, uint32_t rendererFlags);
        // Destroys it
        void exit(void);
        // Begins a frame
        void beginFrame(SDL_Color clearColor);
        // Ends it and presents to screen
        void endFrame(void);
    }
}