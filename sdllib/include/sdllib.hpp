#pragma once
#include "graphics/font.hpp"
#include "graphics/renderer.hpp"
#include "graphics/window.hpp"

#include "input/input.hpp"

namespace sdl
{
    // These start and quit SDL2
    bool init(void);
    void exit(void);
    // This just handles pump events more or less.
    void update(void);
}