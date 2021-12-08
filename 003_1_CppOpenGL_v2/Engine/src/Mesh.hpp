//
// Created by Андрей Марцинкевич on 21.11.21.
//

#ifndef GAME_MESH_HPP
#define GAME_MESH_HPP

#include <Node.hpp>

class ShaderProgram;
class Mesh : public Node
{
public:
    explicit Mesh(std::shared_ptr<ShaderProgram> program);
    ~Mesh() = default;

    std::shared_ptr<ShaderProgram> getProgram() const;

protected:
    std::shared_ptr<ShaderProgram> program;
};


#endif //GAME_MESH_HPP
