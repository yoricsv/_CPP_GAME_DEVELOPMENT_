//
// Created by Андрей Марцинкевич on 22.11.21.
//

#ifndef GAME_SDLMESH_HPP
#define GAME_SDLMESH_HPP

#include <vector>
#include <memory>

#include <Mesh.hpp>
#include <MeshData.hpp>

class ShaderProgram;
class Engine;

class SdlMesh : public Mesh
{
public:
    explicit SdlMesh(const Engine& engine, MeshData data, std::shared_ptr<ShaderProgram> program);
    const MeshData& data();
protected:
    void visitSelf() override;
    MeshData _data;
    const Engine& _engine;
};


#endif //GAME_SDLMESH_HPP
