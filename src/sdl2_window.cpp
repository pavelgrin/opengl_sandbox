#include "./sdl2_window.hpp"

namespace SDL2
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    int createWindow()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return -1;
        }

        SDL_Window* window = SDL_CreateWindow(
            "SDL Window",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCR_WIDTH,
            SCR_HEIGHT,
            0
        );

        if(window == NULL)
        {
            std::cout <<  "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return -1;
        }

        SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

        if(!screenSurface)
        {
            std::cout << "Failed to get the surface from the window\n";
            std::cout << "SDL2 Error: " << SDL_GetError() << std::endl;
            return -1;
        }

        bool keepWindowOpen = true;
        while(keepWindowOpen)
        {
            SDL_Event e;
            while(SDL_PollEvent(&e) > 0)
            {
                switch(e.type)
                {
                    case SDL_QUIT:
                        keepWindowOpen = false;
                        break;
                }

                SDL_UpdateWindowSurface(window);
            }
        }

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }
}
