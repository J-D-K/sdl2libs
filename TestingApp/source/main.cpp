#include <random>

#include "sdl2base.hpp"
#include "sdl2font.hpp"

// Screen width and height
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
// Title text to display
const char *TITLE_TEXT = "EPIC RPG TITLE HERE BRO";
// Color to clear background to
constexpr SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
constexpr SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
// Title text size
constexpr int TITLE_SIZE = 128;

int main(int argc, const char *argv[])
{
    // sdl2libs init/testing
    sdl2base::init();
    SDL_Window *sdlWindow = sdl2base::window::init("sdl2libs Testing App", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    SDL_Renderer *sdlRenderer = sdl2base::renderer::init(sdlWindow, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    sdl2base::input::init();

    // Testing stuff
    // Title font
    sdl2font::font titleFont(sdlRenderer, "testFont.ttf");
    // Center title
    int titleX = (SCREEN_WIDTH / 2) - (titleFont.getTextWidth(TITLE_SIZE, TITLE_TEXT) / 2);
    int titleY = (SCREEN_HEIGHT / 2 - (SCREEN_HEIGHT / 4)); 

    while(true)
    {
        sdl2base::update();
        sdl2base::input::update();

        if(sdl2base::input::keyPressed(SDL_SCANCODE_ESCAPE))
        {
            break;
        }

        sdl2base::renderer::beginFrame(COLOR_WHITE);
        titleFont.renderText(titleX, titleY, TITLE_SIZE, COLOR_BLACK, TITLE_TEXT);
        sdl2base::renderer::endFrame();
    }
    
    sdl2base::renderer::exit();
    sdl2base::window::exit();
    sdl2base::exit();
    return 0;
}