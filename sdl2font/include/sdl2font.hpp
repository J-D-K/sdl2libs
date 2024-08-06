#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <SDL2/SDL.h>

#include "glyphData.h"

namespace sdl2font
{
    // To do: Unicode support.
    class font
    {
        public:
            font() = default;
            // Contructors. These just call font.open(fontPath).
            font(SDL_Renderer *renderer, const char *fontPath);
            font(SDL_Renderer *renderer, const std::string &fontPath);
            // Just quits and frees everything
            ~font();
            // Opens font. Called by constructors.
            bool open(SDL_Renderer *renderer, const char *fontPath);
            // Renders text using font at x, y on target
            void renderText(int x, int y, int fontSize, SDL_Color textColor, const char *format, ...);
            // Gets width of text
            int getTextWidth(int fontSize, const char *format, ...);
            // Returns error string.
            const char *getErrorString(void);

        private:
            // Pointer to SDL_Renderer for glyph textures
            SDL_Renderer *m_Renderer;
            // Freetype library
            FT_Library m_FreeTypeLib;
            // Freetype face
            FT_Face m_FreeTypeFace;
            // Freetype Error
            FT_Error m_FreeTypeError;
            // Buffer to hold font in memory
            std::vector<char> m_FontBuffer;
            // Map of chars and textures
            std::unordered_map<uint64_t, glyphData> m_FontCacheMap;
            // Loads glyph
            glyphData *getGlyph(SDL_Renderer *renderer, char codepoint, int fontSize);
            // Error string
            std::string m_ErrorString;
            // Sets the error string
            void setErrorString(const char *format, ...);
    };
}