#pragma once
#include <string>

#include <SDL2/SDL.h>

namespace sdl
{
    namespace graphics
    {
        namespace renderer
        {
            // Creates render
            bool init(SDL_Window *window, uint32_t rendererFlags);
            // Destroys it
            void exit(void);
            // Returns renderer just in case
            SDL_Renderer *getRenderer(void);
            // Begins a frame
            void beginFrame(SDL_Color clearColor);
            // Ends it and presents to screen
            void endFrame(void);
            // Renders rectangle to screen
            void renderRectangle(int x, int y, int width, int height, SDL_Color color);
        }
    }
}