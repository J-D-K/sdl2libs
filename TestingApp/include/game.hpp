#pragma once
#include <memory>
#include <stack>

#include "gamestate.hpp"

class game
{
    public:
        game(const char *gameTitle, int windowWidth, int windowHeight);
        ~game();

        void update(void);
        void render(void);

        bool isRunning(void);

    private:
        // Whether game successfully started.
        bool m_IsRunning = false;
        // State stack. Maybe unique_ptr would be better?
        std::stack<std::shared_ptr<gamestate>> m_StateStack;
};