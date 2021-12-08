//
// Created by Андрей Марцинкевич on 18.11.21.
//

#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <memory>
#include <string_view>

class Renderer;
class Window
{
public:
    virtual ~Window() = default;

    Window(size_t width, size_t height)
        : _width(width)
        , _height(height)
        {}

    size_t getWidth() const
    {
        return _width;
    }

    size_t getHeight() const
    {
        return _height;
    }

    virtual void update() = 0;
    virtual void swap() = 0;

    virtual std::unique_ptr<Renderer> createRenderer() = 0;

private:
    size_t _width;
    size_t _height;
};
#endif //GAME_WINDOW_HPP
