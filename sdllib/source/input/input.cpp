#include <unordered_map>

#include "input/input.hpp"

// This holds the three states keys can be in.
typedef struct
{
    bool pressed;
    bool held;
    bool released;
} keyState;

namespace
{
    // Map of states for keyboard
    std::unordered_map<SDL_Scancode, keyState> s_KeyStates;
}

void sdl::input::init(void)
{
    // This is to get the number of keys
    int keyCount = 0;
    SDL_GetKeyboardState(&keyCount);

    // This should be enough. Can be adjusted.
    for(int i = 0; i < keyCount; i++)
    {
        s_KeyStates[static_cast<SDL_Scancode>(i)] = 
        {
            .pressed = false,
            .held = false,
            .released = false
        };
    }
}

void sdl::input::update(void)
{
    // Get array of states from SDL
    const uint8_t *keyboardState = SDL_GetKeyboardState(NULL);

    // Loop through map and update them.
    for(auto &key : s_KeyStates)
    {
        if(keyboardState[key.first] && key.second.pressed == false && key.second.held == false)
        {
            key.second.pressed = true;
        }
        else if(keyboardState[key.first] && key.second.pressed == true && key.second.held == false)
        {
            key.second.pressed = false;
            key.second.held = true;
        }
        else if(!keyboardState[key.first] && (key.second.pressed == true || key.second.held == true))
        {
            key.second.pressed = false;
            key.second.held = false;
            key.second.released = true;
        }
        else if(!keyboardState[key.first] && key.second.released == true)
        {
            // Just reset completely
            key.second.pressed = false;
            key.second.held = false;
            key.second.released = false;
        }
    }
}

bool sdl::input::keyPressed(SDL_Scancode keyCode)
{
    return s_KeyStates[keyCode].pressed;
}

bool sdl::input::keyHeld(SDL_Scancode keyCode)
{
    return s_KeyStates[keyCode].held;
}

bool sdl::input::keyReleased(SDL_Scancode keyCode)
{
    return s_KeyStates[keyCode].released;
}