#pragma once

using loadproc      = void* (*)(const char*);
using SDL_GLContext = void*;
struct SDL_Window;

class Window
{
private:
    static SDL_Window* m_window;
    static SDL_GLContext m_context;

    static int m_width;
    static int m_height;

public:
    static int create(const int width, const int height, const char* title);
    static void terminate();

    static void swapBuffers();

    static loadproc getProcAddressFunction();
    static float getElapsedTime();
    static SDL_Window* getWindow();
};
