//
// Created by Андрей Марцинкевич on 20.11.21.
//

#include "SdlRenderer.hpp"
#include "SdlMorphProgram.hpp"

#include <Engine.hpp>
#include <SDL/SdlMesh.hpp>


SdlRenderer::SdlRenderer(const Engine& engine, std::shared_ptr<SDL_Window> sdlWindow)
    : _engine{engine}
    , _sdlWindow(std::move(sdlWindow))
    , _sdlRenderer{SDL_CreateRenderer(_sdlWindow.get(), -1, 0), SDL_DestroyRenderer}
{
}

void SdlRenderer::draw()
{
    auto drawLine = [](auto drawPixel, size_t x0, size_t y0, size_t x1, size_t y1)
    {
        int A, B, sign;
        A = y1 - y0;
        B = x0 - x1;
        if (abs(A) > abs(B)) sign = 1;
        else sign = -1;
        int signa, signb;
        if (A < 0) signa = -1;
        else signa = 1;
        if (B < 0) signb = -1;
        else signb = 1;
        int f = 0;

        drawPixel(x0, y0);
        int x = x0, y = y0;
        if (sign == -1)
        {
            do {
                f += A*signa;
                if (f > 0)
                {
                    f -= B*signb;
                    y += signa;
                }
                x -= signb;
                drawPixel(x, y);
            } while (x != x1 || y != y1);
        }
        else
        {
            do {
                f += B*signb;
                if (f > 0) {
                    f -= A*signa;
                    x -= signb;
                }
                y += signa;
                drawPixel(x, y);
            } while (x != x1 || y != y1);
        }
    };

    SDL_SetRenderDrawColor(_sdlRenderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(_sdlRenderer.get());

    for (const auto& command : _commands)
    {
        auto sdlMesh = std::dynamic_pointer_cast<SdlMesh>(command.mesh);

        if (sdlMesh)
        {
            const auto& data = sdlMesh->data();
            auto sdlProgram = std::dynamic_pointer_cast<SdlShaderProgram>(sdlMesh->getProgram());

            for (size_t i = 0; i < data.indexes.size() - 1; i += 2)
            {
                auto v1 = data.vertices.at(data.indexes[i]);
                auto v2 = data.vertices.at(data.indexes[i + 1]);

                if (sdlProgram)
                {
                    sdlProgram->applyVertex(v1);
                    sdlProgram->applyVertex(v2);
                }

                drawLine([&](size_t x, size_t y)
                         {
                             auto pixel = sdlProgram->getPixel(x, y);
                             SDL_SetRenderDrawColor(_sdlRenderer.get(), pixel.r, pixel.g, pixel.b, 255);
                             SDL_RenderDrawPoint(_sdlRenderer.get(), x, y);
                         },
                         v1.x, v1.y, v2.x, v2.y);
            }
        }
    }

    SDL_RenderPresent(_sdlRenderer.get());

    _commands.clear();
}

std::shared_ptr<ShaderProgram> SdlRenderer::createProgram(std::string_view name) const
{
    if (name == "morph")
    {
        return _engine.createShared<SdlMorphProgram>();
    }

    else return nullptr;
}

std::shared_ptr<Mesh> SdlRenderer::createMesh(MeshData data, std::shared_ptr<ShaderProgram> shaderProgram) const
{
    return _engine.createShared<SdlMesh>(std::move(data), std::move(shaderProgram));
}
