#pragma once

class gamestate
{
    public:
        gamestate(void) { };
        virtual ~gamestate() { };

        virtual void update(void) { };
        virtual void render(void) { };
};