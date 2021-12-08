//
// Created by Андрей Марцинкевич on 22.11.21.
//

#include "SdlMesh.hpp"
#include <Engine.hpp>
#include <Renderer.hpp>

SdlMesh::SdlMesh(const Engine& engine, MeshData data, std::shared_ptr<ShaderProgram> program)
    : Mesh(std::move(program))
    , _engine(engine)
    , _data(std::move(data))
{

}

void SdlMesh::visitSelf()
{
    auto mesh = std::static_pointer_cast<Mesh>(shared_from_this());
    _engine.renderer().addCommand({mesh});
}

const MeshData& SdlMesh::data()
{
    return _data;
}



