#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL_version.h>

class Engine
{
public:

    Engine() = default;
    ~Engine();

    void init()
    {
        SDL_version version = { 0,0,0 };

        SDL_GetVersion(&version);

        printf("SDL2 Version: %d.%d.%d", version.major, version.minor, version.patch);
    }

private:
    struct Pimpl;

    std::unique_ptr<Pimpl> _pimpl;
}

#endif // ENGINE_H