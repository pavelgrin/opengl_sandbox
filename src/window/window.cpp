#include "./window.hpp"

void Window::create(const int scr_width,
                    const int scr_height,
                    const char* scr_header,
                    Render* render) const
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::string error_desc = "SDL couldn't be initialized!\n";
        std::cerr << error_desc << "SDL_Error: " << SDL_GetError() << "\n";
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow(
        scr_header, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scr_width,
        scr_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window == nullptr)
    {
        std::string error_desc = "Window could not be created!\n";
        std::cerr << error_desc << "SDL_Error: " << SDL_GetError() << "\n";

        SDL_Quit();
        return;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        std::string error_desc = "Failed to create OpenGL context!\n";
        std::cerr << error_desc << "SDL_Error: " << SDL_GetError() << "\n";

        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    render->loadGLLoader(static_cast<loadproc>(SDL_GL_GetProcAddress));
    render->updateViewport(scr_width, scr_height);
    render->init();

    float lifetime        = static_cast<float>(SDL_GetTicks64()) / 1000;
    bool keep_window_open = true;

    while (keep_window_open)
    {
        const float current_time = static_cast<float>(SDL_GetTicks64()) / 1000;
        const float dt           = current_time - lifetime;
        lifetime                 = current_time;

        SDL_Event event;
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    render->updateViewport(event.window.data1,
                                           event.window.data2);
                }
                break;
            }
        }

        const uint8_t* keystates = SDL_GetKeyboardState(NULL);
        render->processInput(keystates, dt, &keep_window_open);

        render->frame(dt, lifetime);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
