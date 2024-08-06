#pragma once
#include <SDL2/SDL.h>

typedef struct
{
    int width;
    int height;
    int advanceX;
    int top;
    int left;
    SDL_Texture *glyphTexture;
} glyphData;
