#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

class Engine
{
public:

    explicit Engine();
    ~Engine();

    int init();

private:

    struct Pimpl;
    std::unique_ptr<Pimpl> _pimpl;
};

#endif // ENGINE_H
