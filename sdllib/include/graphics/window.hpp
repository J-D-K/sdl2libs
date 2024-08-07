#pragma once
#include <SDL2/SDL.h>

namespace sdl
{
    namespace graphics
    {
        namespace window
        {
            // Creates a window and returns the pointer to it.
            bool init(const char *windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
            // Destroys the window
            void exit(void);
            // Returns pointer to window
            SDL_Window *getWindow(void);
            // Returns the width of the window
            int getWindowWidth(void);
            int getWindowHeight(void);
        }
    }
}