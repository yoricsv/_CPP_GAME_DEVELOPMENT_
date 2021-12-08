//
// Created by Андрей Марцинкевич on 23.11.21.
//

#include "GlMesh.hpp"

#include <GL/GlHeaders.hpp>
#include <Engine.hpp>
#include <Renderer.hpp>

GlMesh::GlMesh(const Engine &engine,
               MeshData data,
               std::shared_ptr<ShaderProgram> program)
    : Mesh(std::move(program))
    , _engine(engine)
{
    glGenVertexArrays(1, &_VAO);

    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(MeshData::Vertex), data.vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,
                          GL_FLOAT, GL_FALSE,  2 * sizeof(GLfloat), reinterpret_cast<void *>(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indexes.size() * sizeof(std::uint32_t),
                 data.indexes.data(), GL_STATIC_DRAW);

    _count = data.indexes.size();
}


void GlMesh::draw()
{
    glBindVertexArray(_VAO);
    glDrawElements(GL_LINES, _count, GL_UNSIGNED_INT, 0);

    GlCheckError(__FILE__, __LINE__);
}

GlMesh::~GlMesh()
{
    glDeleteBuffers(1, &_VBO);

    if (_IBO != 0)
    {
        glDeleteBuffers(1, &_IBO);
    }


#ifdef GLES
    glDeleteVertexArraysOES(1, &_VAO);
#else
    glDeleteVertexArrays(1, &_VAO);
#endif

    GlCheckError(__FILE__, __LINE__);
}

void GlMesh::visitSelf()
{
    auto mesh = std::static_pointer_cast<Mesh>(shared_from_this());
    _engine.renderer().addCommand({mesh});
}

