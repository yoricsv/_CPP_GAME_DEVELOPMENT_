//
// Created by Андрей Марцинкевич on 23.11.21.
//

#include "GlRenderer.hpp"
#include "GlMesh.hpp"
#include "GlMorphProgram.hpp"

#include <Engine.hpp>

#include <SDL.h>
#include <GL/GlHeaders.hpp>


GlRenderer::GlRenderer(const Engine& engine, SDL_Window* window)
    : _engine(engine)
    , _drawContext{SDL_GL_CreateContext(window), SDL_GL_DeleteContext}
{
    printf("OpenGL version supported by this platform (%s): \n",
           glGetString(GL_VERSION));
}

void GlRenderer::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& command : _commands)
    {
        auto glMesh = std::dynamic_pointer_cast<GlMesh>(command.mesh);

        if (glMesh)
        {
            auto glProgram = std::dynamic_pointer_cast<GlProgram>(glMesh->getProgram());
            if (glProgram)
            {
                glProgram->activate();
                glMesh->draw();
            }
        }
    }
}

std::shared_ptr<Mesh> GlRenderer::createMesh(MeshData data, std::shared_ptr<ShaderProgram> shaderProgram) const
{
    return _engine.createShared<GlMesh>(std::move(data), std::move(shaderProgram));
}

std::shared_ptr<ShaderProgram> GlRenderer::createProgram(std::string_view name) const
{
    if (name == "morph")
    {
        return _engine.createShared<GlMorphProgram>();
    }

    else return nullptr;
}


