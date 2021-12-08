//
// Created by Андрей Марцинкевич on 20.11.21.
//

#ifndef GAME_SDLRENDERER_HPP
#define GAME_SDLRENDERER_HPP

#include <Renderer.hpp>

#include <SDL.h>

#include <memory>
#include <string_view>

class Engine;
class SdlRenderer final : public Renderer
{
public:
    explicit SdlRenderer(const Engine& engine, std::shared_ptr<SDL_Window> sdlWindow);

    void draw() override;

    std::shared_ptr<ShaderProgram> createProgram(std::string_view name) const override;

    std::shared_ptr<Mesh> createMesh(MeshData data, std::shared_ptr<ShaderProgram> shaderProgram) const override;

private:
    std::shared_ptr<SDL_Window> _sdlWindow;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _sdlRenderer;
    const Engine& _engine;
};


#endif //GAME_SDLRENDERER_HPP
