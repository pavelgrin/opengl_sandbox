#include "./window.hpp"


void WindowSDL2::create(const int scr_width, const int scr_height, const char *scr_header) const {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    SDL_Window *window = SDL_CreateWindow(
        scr_header,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        scr_width,
        scr_height,
        0
    );

    if(window == NULL) {
        std::cout <<  "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    if(!screenSurface) {
        std::cout << "Failed to get the surface from the window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << std::endl;
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
