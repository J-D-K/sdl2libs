#include <SDL2/SDL_image.h>

#include "graphics/texture.hpp"
#include "graphics/renderer.hpp"

sdl::graphics::texture::texture(const char *filePath)
{
    texture::load(filePath);
}

sdl::graphics::texture::texture(const std::string &filePath)
{
    texture::load(filePath.c_str());
}

sdl::graphics::texture::~texture()
{
    SDL_DestroyTexture(m_Texture);
}

bool sdl::graphics::texture::load(const char *filePath)
{
    // Try to load image.
    SDL_Surface *imageSurface = IMG_Load(filePath);
    // Bail if image wasn't found/loaded.
    if(imageSurface == NULL)
    {
        return false;
    }
    // Get width and height
    m_Width = imageSurface->w;
    m_Height = imageSurface->h;
    // Convert to texture.
    m_Texture = SDL_CreateTextureFromSurface(sdl::graphics::renderer::getRenderer(), imageSurface);
}

void sdl::graphics::texture::renderAt(int x, int y)
{
    SDL_Rect sourceRect = { .x = 0, .y = 0, .w = m_Width, .h = m_Height };
    SDL_Rect destinationRect = { .x = x, .y = y, .w = m_Width, .h = m_Height };
    SDL_RenderCopy(sdl::graphics::renderer::getRenderer(), m_Texture, &sourceRect, &destinationRect);
}

void sdl::graphics::texture::renderAtStretched(int x, int y, int width, int height)
{
    SDL_Rect sourceRect = { .x = 0, .y = 0, .w = m_Width, .h = m_Height };
    SDL_Rect destinationRect = { .x = x, .y = y, .w = width, .h = height };
    SDL_RenderCopy(sdl::graphics::renderer::getRenderer(), m_Texture, &sourceRect, &destinationRect);
}

void sdl::graphics::texture::renderPartAt(int sourceX, int sourceY, int sourceWidth, int sourceHeight, int destinationX, int destinationY, int destinationWidth, int destinationHeight)
{
    SDL_Rect sourceRect = { .x = sourceX, .y = sourceY, .w = sourceWidth, .h = sourceHeight };
    SDL_Rect destinationRect = { .x = destinationX, .y = destinationY, .w = destinationWidth, .h = destinationHeight };
    SDL_RenderCopy(sdl::graphics::renderer::getRenderer(), m_Texture, &sourceRect, &destinationRect);
}