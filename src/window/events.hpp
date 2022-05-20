#pragma once

#include "./states.hpp"

struct SDL_Window;

class Events
{
private:
    static SDL_Window* m_window;

public:
    static EventStates states;
    static EventActions actions;

    static void init(SDL_Window* m_window, int width, int height);
    static void fini();

    static void poll();
};
