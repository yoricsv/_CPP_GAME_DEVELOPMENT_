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

Engine::~Engine() = default; // for Windows

