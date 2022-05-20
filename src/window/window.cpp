#include "./window.hpp"
#include <SDL.h>
#include <iostream>

SDL_Window* Window::m_window;
SDL_GLContext Window::m_context;

int Window::m_width  = 0;
int Window::m_height = 0;

int Window::create(const int width, const int height, const char* title)
{
    m_width  = width;
    m_height = height;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        const char* error_desc = "SDL couldn't be initialized!\n";
        std::cerr << error_desc << "SDL_Error: " << SDL_GetError() << "\n";

        terminate();
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                m_width, m_height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (m_window == NULL)
    {
        const char* error_desc = "Window could not be created!\n";
        std::cerr << error_desc << "SDL_Error: " << SDL_GetError() << "\n";

        terminate();
        return -1;
    }

    SDL_GLContext m_context = SDL_GL_CreateContext(m_window);

    if (m_context == NULL)
    {
        const char* error_desc = "Failed to create OpenGL context!\n";
        std::cerr << error_desc << "SDL_Error: " << SDL_GetError() << "\n";

        terminate();
        return -1;
    }

    return 0;
}

void Window::terminate()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::swapBuffers()
{
    SDL_GL_SwapWindow(m_window);
}

loadproc Window::getProcAddressFunction()
{
    return SDL_GL_GetProcAddress;
}

float Window::getElapsedTime()
{
    return static_cast<float>(SDL_GetTicks64()) / 1000;
}

SDL_Window* Window::getWindow()
{
    return m_window;
}
