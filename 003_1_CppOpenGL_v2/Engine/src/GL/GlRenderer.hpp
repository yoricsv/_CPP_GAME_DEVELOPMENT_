//
// Created by Андрей Марцинкевич on 23.11.21.
//

#ifndef GAME_GLRENDERER_HPP
#define GAME_GLRENDERER_HPP

#include <Renderer.hpp>

class SDL_Window;
class Engine;
class GlRenderer final : public Renderer
{
public:
    explicit GlRenderer(const Engine& engine, SDL_Window* window);

    void draw() override;

    std::shared_ptr<Mesh> createMesh(MeshData data, std::shared_ptr<ShaderProgram> shaderProgram) const override;
    std::shared_ptr<ShaderProgram> createProgram(std::string_view name) const override;

private:
    const Engine& _engine;
    std::unique_ptr<void, void(*)(void*)> _drawContext;
};


#endif //GAME_GLRENDERER_HPP
