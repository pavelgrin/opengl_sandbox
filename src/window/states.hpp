#pragma once

#include <map>

enum class KeyCode;
enum class MouseCode;

struct Resolution
{
    bool changed{false};
    int width{0};
    int height{0};
};

struct EventStates
{
    bool keep_window_open{true};
    bool cursor_locked{false};

    Resolution window_size;

    std::map<KeyCode, bool> keystates;
    std::map<MouseCode, bool> mousestates;

    int mouse_x_delta{0};
    int mouse_y_delta{0};
    int mouse_wheel_delta{0};
};

struct EventActions
{
    void closeWindow(EventStates* states)
    {
        states->keep_window_open = false;
    }

    void toggleCursor(EventStates* states, bool value)
    {
        states->cursor_locked = value;
    }

    void updateWindowSize(EventStates* states, bool changed,
                          const int width = 0, const int height = 0)
    {
        states->window_size.changed = changed;
        states->window_size.width   = changed ? width : states->window_size.width;
        states->window_size.height  = changed ? height : states->window_size.height;
    }

    void updateKeyStates(EventStates* states, KeyCode code, bool is_pressed)
    {
        states->keystates[code] = is_pressed;
    }

    void updateMouseStates(EventStates* states, MouseCode code, bool is_pressed)
    {
        states->mousestates[code] = is_pressed;
    }

    void updateMouseWheelDelta(EventStates* states, int value)
    {
        states->mouse_wheel_delta = value;
    }

    void updateMousePosDelta(EventStates* states, int d_x, int d_y)
    {
        states->mouse_x_delta = d_x;
        states->mouse_y_delta = d_y;
    }
};

// -----------------------------------------------------------------------------
enum class MouseCode
{
    Left   = 1,
    Middle = 2,
    Right  = 3,
};

enum class KeyCode
{
    // clang-format off
    A =  4, B =  5, C =  6, D =  7, E =  8, F =  9, G = 10, H = 11, I = 12,
    J = 13, K = 14, L = 15, M = 16, N = 17, O = 18, P = 19, Q = 20, R = 21,
    S = 22, T = 23, U = 24, V = 25, W = 26, X = 27, Y = 28, Z = 29,

    N1 = 30, N2 = 31, N3 = 32, N4 = 33, N5 = 34,
    N6 = 35, N7 = 36, N8 = 37, N9 = 38, N0 = 39,

    Return    = 40,
    Escape    = 41,
    Backspace = 42,
    Tab       = 43,
    Space     = 44,

    LCtrl     = 224,
    LShift    = 225,
    LAlt      = 226,
    LGui      = 227,
    RCtrl     = 228,
    RShift    = 229,
    RAlt      = 230,
    RGui      = 231,
    // clang-format on
};
