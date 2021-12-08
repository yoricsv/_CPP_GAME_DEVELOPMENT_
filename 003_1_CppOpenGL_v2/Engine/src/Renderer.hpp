//
// Created by Андрей Маsрцинкевич on 20.11.21.
//

#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <vector>
#include <string_view>

#include <MeshData.hpp>

class Mesh;
class ShaderProgram;
class Renderer
{
public:
    virtual ~Renderer() = default;

    struct Command
    {
        std::shared_ptr<Mesh> mesh;
    };

    void addCommand(Command command) const
    {
        _commands.push_back(std::move(command));
    }

    virtual void draw() = 0;

    virtual std::shared_ptr<Mesh> createMesh(MeshData data, std::shared_ptr<ShaderProgram> shaderProgram) const = 0;
    virtual std::shared_ptr<ShaderProgram> createProgram(std::string_view name) const = 0;

protected:
    mutable std::vector<Command> _commands;
};

#endif //GAME_RENDERER_HPP
