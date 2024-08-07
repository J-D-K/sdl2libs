#pragma once
#include <SDL2/SDL.h>

namespace sdl
{
    namespace graphics
    {
        typedef struct
        {
            int width;
            int height;
            int advanceX;
            int top;
            int left;
            SDL_Texture *glyphTexture;
        } glyphData;
    }
}
