#include "./events.hpp"
#include <SDL.h>

SDL_Window* Events::m_window;

EventStates Events::states;
EventActions Events::actions;

void Events::init(SDL_Window* window, int width, int height)
{
    m_window = window;
    actions.updateWindowSize(&states, true, width, height);
}

void Events::fini() {}

void Events::poll()
{
    actions.updateWindowSize(&states, false);
    actions.updateMouseWheelDelta(&states, 0);
    actions.updateMousePosDelta(&states, 0, 0);

    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            actions.closeWindow(&states);
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                const int width  = event.window.data1;
                const int height = event.window.data2;

                actions.updateWindowSize(&states, true, width, height);
            }
            break;
        case SDL_MOUSEWHEEL:
            actions.updateMouseWheelDelta(&states,
                                          states.mouse_wheel_delta + event.wheel.y);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            bool is_pressed = event.key.state == SDL_PRESSED;
            KeyCode code    = static_cast<KeyCode>(event.key.keysym.scancode);

            actions.updateKeyStates(&states, code, is_pressed);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            bool is_pressed = event.button.state == SDL_PRESSED;
            MouseCode code  = static_cast<MouseCode>(event.button.button);

            actions.updateMouseStates(&states, code, is_pressed);
            break;
        }
        }
    }

    int mouse_x_delta{0};
    int mouse_y_delta{0};
    const uint32_t mouse_state_mask = SDL_GetRelativeMouseState(&mouse_x_delta,
                                                                &mouse_y_delta);

    actions.updateMousePosDelta(&states, mouse_x_delta, mouse_y_delta);

    if (states.cursor_locked)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_WarpMouseInWindow(m_window,
                              states.window_size.width / 2,
                              states.window_size.height / 2);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}
