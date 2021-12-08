//
// Created by Андрей Марцинкевич on 21.11.21.
//

#include "Mesh.hpp"

std::shared_ptr<ShaderProgram> Mesh::getProgram() const
{
    return program;
}

Mesh::Mesh(std::shared_ptr<ShaderProgram> program)
        : program(std::move(program))
{}
