#pragma once
#include <SDL2/SDL.h>

namespace sdl
{
    namespace input
    {
        // Inits keyboard handling and mouse maybe?
        void init(void);
        // Updates keyStates
        void update(void);
        // Return if key is pressed, held, or released.
        bool keyPressed(SDL_Scancode keyCode);
        bool keyHeld(SDL_Scancode keyCode);
        bool keyReleased(SDL_Scancode keyCode);
    }
}
