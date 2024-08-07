#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <SDL2/SDL.h>

#include "graphics/glyphData.hpp"

namespace sdl
{
    namespace graphics
    {
        // To do: Unicode support.
        class font
        {
            public:
                font() = default;
                // Contructors. These just call font.open(fontPath).
                font(const char *fontPath);
                font(const std::string &fontPath);
                // Just quits and frees everything
                ~font();
                // Opens font. Called by constructors.
                bool load(const char *fontPath);
                // Renders text using font at x, y on target
                void renderText(int x, int y, int fontSize, SDL_Color textColor, const char *format, ...);
                // Gets width of text
                int getTextWidth(int fontSize, const char *format, ...);
                // Returns error string.
                const char *getErrorString(void);

            private:
                // Freetype library
                FT_Library m_FreeTypeLib;
                // Freetype face
                FT_Face m_FreeTypeFace;
                // Freetype Error
                FT_Error m_FreeTypeError;
                // Buffer to hold font in memory
                std::vector<char> m_FontBuffer;
                // Map of chars and textures
                std::unordered_map<uint64_t, sdl::graphics::glyphData> m_FontCacheMap;
                // Loads or retrieves glyphData pointer from map.
                sdl::graphics::glyphData *getGlyph(SDL_Renderer *renderer, char codepoint, int fontSize);
                // Error string
                std::string m_ErrorString;
                // Sets the error string
                void setErrorString(const char *format, ...);
        };
    }
}