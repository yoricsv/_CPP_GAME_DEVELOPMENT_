#include "Engine.h"
#include <SDL.h>

struct Engine::Pimpl
{
    SDL_Color color;
};

Engine::Engine() noexcept
{
    _pimpl = std::make_unique<Engine::Pimpl>();
    _pimpl -> color;
}
Engine::~Engine() = default; // for Windows

int Engine::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window * window =
        SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0 | SDL_WINDOW_ALLOW_HIGHDPI
        );

    if (!window)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    for(;;)
    {

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}







// TODO:
//    Uint32  windows_flags = SDL_WINDOW_SHOWN;
//    if(_renderer_mode == Render)

//    SDL_UpdateWindowSurface(window);
//    SDL_Renderer * renderer =
//        SDL_CreateRenderer(
//            window,
//            -1,
//            SDL_RENDERER_SOFTWARE
//        );
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(renderer);
//    SDL_RenderPresent(renderer);

// TODO:
//    bool keep_window_open = true;
//    while(keep_window_open)
//    {
//        SDL_Event e;
//        while(SDL_PollEvent(&e) > 0)
//        {
//            SDL_UpdateWindowSurface(window);
//        }
//        return EXIT_SUCCESS;
//    }
