#pragma once
#include <string>
#include <SDL2/SDL.h>

// This contains the width and height of a texture so I don't have to call SDL_Query to get them.
namespace sdl
{
    namespace graphics
    {
        class texture
        {
            public:
                // Default constructor
                texture() = default;
                // These ones call load
                texture(const char *filePath);
                texture(const std::string &filePath);
                // Deconstructor. Destroys SDL_Texture.
                ~texture();
                // Loads the texture using SDL_image
                bool load(const char *filePath);
                // Renders texture normally at x and y
                void renderAt(int x, int y);
                // Renders texture at x and y, but stretched to width and height
                void renderAtStretched(int x, int y, int width, int height);
                // Renders part of the texture at x and y
                void renderPartAt(int sourceX, int sourceY, int sourceWidth, int sourceHeight, int destinationX, int destinationY, int destinationWidth, int destinationHeight);

            private:
                // Actual SDL texture pointer
                SDL_Texture *m_Texture = NULL;
                // Width and height of texture.
                int m_Width = 0;
                int m_Height = 0;
        };
    }
}
