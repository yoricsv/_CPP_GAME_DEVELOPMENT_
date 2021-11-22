//
// Created by Андрей Марцинкевич on 17.11.21.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>

class Engine
{
public:
    explicit Engine();
    ~Engine();

    void init();
private:
    struct Pimpl;
    std::unique_ptr< Pimpl> _pimpl;
};


#endif //SDLLINK_ENGINE_HPP
