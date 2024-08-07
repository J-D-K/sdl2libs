#include <array>
#include <cstdarg>
#include <cstring>
#include <fstream>

#include "graphics/font.hpp"
#include "graphics/renderer.hpp"

// This is the buffer size used for va operation
constexpr int VA_BUFFER_SIZE = 0x1000;
// This is the base color white used for surface
constexpr uint32_t PIXEL_WHITE_COLOR = 0xFFFFFF00;
// These are for SDL_Surface
constexpr uint32_t SURFACE_RED_MASK = 0xFF000000;
constexpr uint32_t SURFACE_GREEN_MASK = 0x00FF0000;
constexpr uint32_t SURFACE_BLUE_MASK = 0x0000FF00;
constexpr uint32_t SURFACE_ALPHA_MASK = 0x000000FF;


sdl::graphics::font::font(const char *fontPath)
{
    font::load(fontPath);
}

sdl::graphics::font::font(const std::string &fontPath)
{
    font::load(fontPath.c_str());
}

sdl::graphics::font::~font()
{
    // Loop through and destroy textures.
    for(auto &glyphData : m_FontCacheMap)
    {
        SDL_DestroyTexture(glyphData.second.glyphTexture);
    }

    // Free face
    m_FreeTypeError = FT_Done_Face(m_FreeTypeFace);
    if(m_FreeTypeError != 0)
    {
        font::setErrorString("Error freeing FreeType face: %i.", m_FreeTypeError);
    }
    
    // Free library
    m_FreeTypeError = FT_Done_FreeType(m_FreeTypeLib);
    if(m_FreeTypeError != 0)
    {
        font::setErrorString("Error freeing FreeType library: %i.", m_FreeTypeError);
    }
}

bool sdl::graphics::font::load(const char *fontPath)
{
    // Get font size
    std::ifstream fontStream(fontPath, std::ios::binary);
    fontStream.seekg(0, std::ios::end);
    size_t fontSize = fontStream.tellg();
    fontStream.seekg(0, std::ios::beg);

    // Resize vector for font
    m_FontBuffer.resize(fontSize);

    // Read it to memory
    fontStream.read(m_FontBuffer.data(), fontSize);

    // Try to init freetype library
    m_FreeTypeError = FT_Init_FreeType(&m_FreeTypeLib);
    if(m_FreeTypeError != 0)
    {
        font::setErrorString("Error initalizing FreeType library: %i.", m_FreeTypeError);
        return false;
    }

    // Try to init face
    m_FreeTypeError = FT_New_Memory_Face(m_FreeTypeLib, reinterpret_cast<FT_Byte *>(m_FontBuffer.data()), m_FontBuffer.size(), 0, &m_FreeTypeFace);
    if(m_FreeTypeError != 0)
    {
        font::setErrorString("Error creating new FreeType face: %i.", m_FreeTypeError);
        return false;
    }
    return true;
}

void sdl::graphics::font::renderText(int x, int y, int fontSize, SDL_Color textColor, const char *format, ...)
{
    // Resize to fontSize in pixels
    FT_Set_Char_Size(m_FreeTypeFace, 0, fontSize * 64, 90, 90);

    // Working x so we can line break
    int workingX = x;

    // Pointer to renderer since we're rendering stuff
    SDL_Renderer *renderer = sdl::graphics::renderer::getRenderer();

    // Va buffer
    std::array<char, VA_BUFFER_SIZE> vaBuffer;
    
    // Va
    std::va_list vaList;
    va_start(vaList, format);
    vsnprintf(vaBuffer.data(), VA_BUFFER_SIZE, format, vaList);
    va_end(vaList);

    // Get string length for loop
    int stringLength = std::strlen(vaBuffer.data());

    // Loop and render it to target
    for(int i = 0; i < stringLength; i++)
    {
        if(vaBuffer.at(i) == '\n')
        {
            workingX = x;
            y += fontSize + (fontSize / 4);
            continue;
        }

        // Get glyphData for current character
        glyphData *currentGlyph = font::getGlyph(renderer, vaBuffer.at(i), fontSize);
        if(currentGlyph != NULL)
        {
            // Rects to render
            SDL_Rect sourceRect = 
            {
                .x = 0,
                .y = 0,
                .w = currentGlyph->width,
                .h = currentGlyph->height
            };

            SDL_Rect destinationRect = 
            {
                .x = workingX + currentGlyph->left,
                .y = y + (fontSize - currentGlyph->top),
                .w = currentGlyph->width,
                .h = currentGlyph->height
            };
            // Set color
            SDL_SetTextureColorMod(currentGlyph->glyphTexture, textColor.r, textColor.g, textColor.b);
            // Render
            SDL_RenderCopy(renderer, currentGlyph->glyphTexture, &sourceRect, &destinationRect);
            // Add to workingX
            workingX += currentGlyph->advanceX;
        }
    }
}

int sdl::graphics::font::getTextWidth(int fontSize, const char *format, ...)
{
    // Return size
    int textWidth = 0;

    // Resize font just in case
    FT_Set_Char_Size(m_FreeTypeFace, 0, fontSize * 64, 90, 90);

    // Need renderer for new glyphs
    SDL_Renderer *renderer = sdl::graphics::renderer::getRenderer();

    // Va
    std::array<char, VA_BUFFER_SIZE> vaBuffer;
    std::va_list vaList;
    va_start(vaList, format);
    vsnprintf(vaBuffer.data(), VA_BUFFER_SIZE, format, vaList);
    va_end(vaList);

    // String length
    int stringLength = std::strlen(vaBuffer.data());

    // Loop through and get size
    for(int i = 0; i < stringLength; i++)
    {
        // Ignore line breaks
        if(vaBuffer.at(i) == '\n')
        {
            continue;
        }

        glyphData *currentGlyph = font::getGlyph(renderer, vaBuffer.at(i), fontSize);
        if(currentGlyph != NULL)
        {
            textWidth += currentGlyph->advanceX;
        }
    }
    return textWidth;
}

void sdl::graphics::font::setErrorString(const char *format, ...)
{
    // Array  buffer
    std::array<char, VA_BUFFER_SIZE> vaBuffer;

    // VA
    std::va_list vaList;
    va_start(vaList, format);
    vsnprintf(vaBuffer.data(), VA_BUFFER_SIZE, format, vaList);
    va_end(vaList);

    // Just set string
    m_ErrorString = vaBuffer.data();
}

sdl::graphics::glyphData *sdl::graphics::font::getGlyph(SDL_Renderer *renderer, char codepoint, int fontSize)
{
    // This is kind of like an ID used to identify the glyph
    uint64_t codepointID = static_cast<uint64_t>(codepoint) << 56 | fontSize;

    // Search map for glyph first and return it if found.
    if(m_FontCacheMap.find(codepointID) != m_FontCacheMap.end())
    {
        return &m_FontCacheMap.at(codepointID);
    }

    // Try to load it of not found.
    FT_Int glyphIndex = FT_Get_Char_Index(m_FreeTypeFace, codepoint);
    FT_Error loadGlyphError = FT_Load_Glyph(m_FreeTypeFace, glyphIndex, FT_LOAD_RENDER);
    if(loadGlyphError != 0)
    {
        font::setErrorString("Error loading glyph for %c.", codepoint);
        return NULL;
    }

    // Glyph slot
    FT_GlyphSlot glyphSlot = m_FreeTypeFace->glyph;
    // Pointer to bitmap to convert to surface->texture
    FT_Bitmap glyphBitmap = glyphSlot->bitmap;
    // Pointer to actual alpha/pixel data
    unsigned char *glyphAlphaData = glyphBitmap.buffer;
    // GlyphSize
    int glyphSize = glyphBitmap.width * glyphBitmap.rows;
    // Create surface from FreeType bitmap
    SDL_Surface *glyphSurface = SDL_CreateRGBSurface(0, glyphBitmap.width, glyphBitmap.rows, 32, SURFACE_RED_MASK, SURFACE_GREEN_MASK, SURFACE_BLUE_MASK, SURFACE_ALPHA_MASK);
    if(glyphSurface == NULL)
    {
        font::setErrorString("Surface is null, %s.", SDL_GetError());
        return NULL;
    }

    // Pointer to surface bitmap data
    uint32_t *glyphPixelData = reinterpret_cast<uint32_t *>(glyphSurface->pixels);

    // Loop through bitmap and construct full glyph in white
    for(int i = 0; i < glyphSize; i++)
    {
        *glyphPixelData++ = PIXEL_WHITE_COLOR | *glyphAlphaData++;
    }

    // Convert surface to SDL_Texture
    SDL_Texture *glyphTexture = SDL_CreateTextureFromSurface(renderer, glyphSurface);
    // Free surface, no longer needed.
    SDL_FreeSurface(glyphSurface);

    // Add it to map
    m_FontCacheMap[codepointID] = 
    {
        .width = static_cast<int>(glyphBitmap.width),
        .height = static_cast<int>(glyphBitmap.rows),
        .advanceX = static_cast<int>(glyphSlot->advance.x) >> 6,
        .top = static_cast<int>(glyphSlot->bitmap_top),
        .left = static_cast<int>(glyphSlot->bitmap_left),
        .glyphTexture = glyphTexture
    };

    // Return it
    return &m_FontCacheMap.at(codepointID);
}

const char *sdl::graphics::font::getErrorString(void)
{
    return m_ErrorString.c_str();
}