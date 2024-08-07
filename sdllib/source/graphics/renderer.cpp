#include <SDL2/SDL_image.h>

#include "logger.hpp"
#include "graphics/renderer.hpp"

namespace
{
    SDL_Renderer *s_Renderer = NULL;
}

bool sdl::graphics::renderer::init(SDL_Window *window, uint32_t rendererFlags)
{
    s_Renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(s_Renderer == NULL)
    {
        logger::log("Error creating SDL2 Renderer: %s.", SDL_GetError());
        return false;
    }
    return true;
}

void sdl::graphics::renderer::exit(void)
{
    if(s_Renderer != NULL)
    {
        SDL_DestroyRenderer(s_Renderer);
    }
}

SDL_Renderer *sdl::graphics::renderer::getRenderer(void)
{
    return s_Renderer;
}

void sdl::graphics::renderer::beginFrame(SDL_Color clearColor)
{
    // Clear frame to black
    SDL_SetRenderDrawColor(s_Renderer, clearColor.r, clearColor.g, clearColor.b, 0xFF);
    // Clear
    SDL_RenderClear(s_Renderer);
}

void sdl::graphics::renderer::endFrame(void)
{
    SDL_RenderPresent(s_Renderer);
}

void sdl::graphics::renderer::renderRectangle(int x, int y, int width, int height, SDL_Color color)
{
    // SDL rect with coordinates
    SDL_Rect rectCoordinates = { .x = x, .y = y, .w = width, .h = height };
    // Set draw color for rect.
    SDL_SetRenderDrawColor(s_Renderer, color.r, color.g, color.b, color.a);
    // Render it
    SDL_RenderFillRect(s_Renderer, &rectCoordinates);
}
