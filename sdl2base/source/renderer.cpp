#include "logger.hpp"
#include "renderer.hpp"

namespace
{
    SDL_Renderer *s_Renderer = NULL;
}

SDL_Renderer *sdl2base::renderer::init(SDL_Window *window, uint32_t rendererFlags)
{
    s_Renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(s_Renderer == NULL)
    {
        logger::log("Error creating SDL2 Renderer: %s.", SDL_GetError());
        return NULL;
    }
    return s_Renderer;
}

void sdl2base::renderer::exit(void)
{
    if(s_Renderer != NULL)
    {
        SDL_DestroyRenderer(s_Renderer);
    }
}
void sdl2base::renderer::beginFrame(SDL_Color clearColor)
{
    // Clear frame to black
    SDL_SetRenderDrawColor(s_Renderer, clearColor.r, clearColor.g, clearColor.b, 0xFF);
    // Clear
    SDL_RenderClear(s_Renderer);
}

void sdl2base::renderer::endFrame(void)
{
    SDL_RenderPresent(s_Renderer);
}