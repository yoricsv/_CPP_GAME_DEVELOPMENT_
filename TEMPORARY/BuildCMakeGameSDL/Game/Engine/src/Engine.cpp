//
// Created by Андрей Марцинкевич on 17.11.21.
//

#include "Engine.hpp"

#include <SDL.h>

struct Engine::Pimpl
{

};

Engine::Engine()
{
    _pimpl = std::make_unique<Engine::Pimpl>();
}

void Engine::init()
{
    SDL_version version   = { 0, 0, 0 };

    SDL_GetVersion(&version);

    printf("SDL Version: %d.%d.%d", version.major, version.minor, version.patch);
}

Engine::~Engine() = default;
