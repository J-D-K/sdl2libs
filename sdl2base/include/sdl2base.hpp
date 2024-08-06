#pragma once
#include "window.hpp"
#include "renderer.hpp"
#include "input.hpp"

namespace sdl2base
{
    // These start and quit SDL2
    bool init(void);
    void exit(void);
    // This just handles pump events more or less.
    void update(void);
}