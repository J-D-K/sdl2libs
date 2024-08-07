#pragma once
#include "game.hpp"
#include "gamestate.hpp"
#include "sdllib.hpp"

class titlestate : public gamestate
{
    public:
        titlestate(void);
        ~titlestate();

        void update(void);
        void render(void);

    private:
        // Title screen font
        sdl::graphics::font m_TitleFont;
        // Width of title text
        int m_TitleTextWidth = 0;
        // Centered X of text
        int m_TitleTextX = 0;
        // Y position. Calculated on construction
        int m_TitleTextY = 0;
};