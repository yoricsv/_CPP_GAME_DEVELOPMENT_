#include "Engine.h"
#include <SDL.h>

struct Engine::Pimpl
{
    SDL_Color color;
};

Engine::Engine()
{
    _pimpl = std::make_unique<Engine::Pimpl>();
    _pimpl -> color;
}

int Engine::init()
{
//    if (!SDL_Init(SDL_INIT_EVERYTHING))
//    {
//        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//        return EXIT_FAILURE;
//    }

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window * window =
        SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
//            0 |
//            SDL_WINDOW_ALLOW_HIGHDPI |
//            SDL_WINDOW_OPENGL |
            SDL_WINDOW_SHOWN

        );

//    if (!window)
//    {
//        printf("Could not create window: %s\n", SDL_GetError());
//        return EXIT_FAILURE;
//    }

    bool keep_window_open = true;

    while(keep_window_open)
    {
        SDL_Event event;

        if(SDL_PollEvent(&event) > 0)
        {
            SDL_UpdateWindowSurface(window);

            SDL_Renderer * renderer =
                SDL_CreateRenderer(
                    window,
                    -1,
                    SDL_RENDERER_SOFTWARE
                );

            SDL_SetRenderDrawColor(
                renderer,
                0,
                0,
                0,
                SDL_ALPHA_OPAQUE
            );

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);

            if (event.type == SDL_QUIT)
            {
                keep_window_open = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

Engine::~Engine() = default; // for Windows


// TODO:
//    Uint32  windows_flags = SDL_WINDOW_SHOWN;
//    if(_renderer_mode == Render)

