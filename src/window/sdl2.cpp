#include "./window.hpp"

void WindowSDL2::create(const int scr_width, const int scr_height, const char *scr_header) const {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string error_desc = "SDL could not initialize!\n";
        throw error_desc + "SDL_Error: " + (std::string)SDL_GetError() + "\n";
    }

    SDL_Window *window = SDL_CreateWindow(
        scr_header,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        scr_width,
        scr_height,
        0
    );

    if (window == NULL) {
        std::string error_desc = "Window could not be created!\n";
        throw error_desc + "SDL_Error: " + (std::string)SDL_GetError() + "\n";
    }

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    if (!screenSurface) {
        std::string error_desc = "Failed to get the surface from the window!\n";
        throw error_desc + "SDL_Error: " + (std::string)SDL_GetError() + "\n";
    }

    bool keepWindowOpen = true;
    while(keepWindowOpen) {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0) {
            switch(e.type) {
                case SDL_QUIT:
                    keepWindowOpen = false;
                    break;
            }

            SDL_UpdateWindowSurface(window);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
