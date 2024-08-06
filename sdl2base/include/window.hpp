#pragma once
#include <SDL2/SDL.h>

namespace sdl2base
{
    namespace window
    {
        // Creates a window and returns the pointer to it.
        SDL_Window *init(const char *windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        // Destroys the window
        void exit(void);
    }
}