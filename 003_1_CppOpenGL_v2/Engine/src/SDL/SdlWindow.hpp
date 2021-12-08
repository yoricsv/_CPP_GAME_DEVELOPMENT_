//
// Created by Андрей Марцинкевич on 18.11.21.
//

#ifndef GAME_SDLWINDOW_HPP
#define GAME_SDLWINDOW_HPP

#include <Window.hpp>

#include <SDL.h>
#include <string_view>

class Engine;
class SdlWindow final : public Window
{
public:
    enum class RenderMode
    {
        OpenGl,
        Software
    };

    SdlWindow(const Engine& engine,
              std::string_view name,
              size_t width,
              size_t height,
              RenderMode renderMode);

    std::unique_ptr<Renderer> createRenderer() override;

    void update() override;

    void swap() override;

private:
    std::shared_ptr<SDL_Window> _window;
    RenderMode _renderMode;
    const Engine& _engine;
};


#endif //GAME_SDLWINDOW_HPP
