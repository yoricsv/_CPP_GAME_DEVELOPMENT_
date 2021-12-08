//
// Created by Андрей Марцинкевич on 23.11.21.
//

#ifndef GAME_GLMESH_HPP
#define GAME_GLMESH_HPP

#include <Mesh.hpp>
#include <MeshData.hpp>

class Engine;
class GlMesh final : public Mesh
{
public:
    explicit GlMesh(const Engine& engine,
                    MeshData data,
                    std::shared_ptr<ShaderProgram> program);

    virtual ~GlMesh();

    void visitSelf() override;
    void draw();


private:
    uint32_t _VAO = 0;
    uint32_t _VBO = 0;
    uint32_t _IBO = 0;

    uint32_t _count;

    const Engine& _engine;
};


#endif //GAME_GLMESH_HPP
