//
// Created by Андрей Марцинкевич on 21.11.21.
//

#include "SdlMorphProgram.hpp"
#include <Utils/CppExt.hpp>
#include <Engine.hpp>

SdlMorphProgram::SdlMorphProgram(const Engine& engine)
 : reg(engine.eventsManager(), ext::genUniqueObjectId())
{
    reg += [this](const MouseEvent& e)
    {
        if (e.type == MouseEvent::Type::LButtonDown)
        {
            MousePos pos{};
            pos.x = e.x;
            pos.y = e.y;
            _mousePos = pos;
        }

        if (e.type == MouseEvent::Type::LButtonUp)
        {
            _mousePos = std::nullopt;
        }

        if (e.type == MouseEvent::Type::Move)
        {
            if (_mousePos)
            {
                _mousePos->x = e.x;
                _mousePos->y = e.y;
            }
        }
    };

}


void SdlMorphProgram::applyVertex(MeshData::Vertex &vertex)
{
    if (_mousePos)
    {
        int diffX = vertex.x - _mousePos->x;
        int diffY = vertex.y - _mousePos->y;

        float len = std::sqrt(diffX * diffX + diffY * diffY);

        if (len > 0 && len < 100.0f)
        {
            float normalX = diffX / len;
            float normalY = diffY / len;

            float coef = 1.0 - std::pow(len, 4) / std::pow(100, 4);

            vertex.x += normalX * 18.0 * coef;
            vertex.y += normalY * 18.0 * coef;
        }
    }
}

SdlShaderProgram::Pixel SdlMorphProgram::getPixel(size_t x, size_t y)
{
    Pixel pixel{};
    pixel.g = 255;

    if (_mousePos)
    {
        int diffX = x - _mousePos->x;
        int diffY = y - _mousePos->y;

        float len = std::sqrt(diffX * diffX + diffY * diffY);

        if (len > 0 && len < 100.0f)
        {
            float coef = 1.0 - std::pow(len, 2) / std::pow(100, 2);
            pixel.r = 255 * coef;
            pixel.g = 255 * (1.0 - coef);
        }
    }

    return pixel;

}

