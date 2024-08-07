#include "game.hpp"
#include "sdllib.hpp"

int main(int argc, const char *argv[])
{
    game testGame("Test", 2560, 1440);

    while(testGame.isRunning())
    {
        testGame.update();
        testGame.render();
    }
}