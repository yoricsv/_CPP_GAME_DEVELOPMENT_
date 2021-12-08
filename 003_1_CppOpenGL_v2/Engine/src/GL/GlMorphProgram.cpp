//
// Created by Андрей Марцинкевич on 23.11.21.
//

#include "GlMorphProgram.hpp"
#include <GL/GlHeaders.hpp>
#include <Engine.hpp>
#include <Window.hpp>

namespace
{
    constexpr auto vs_program =
R"(
#version 330 core

layout (location = 0) in vec2 position;

out vec2 oPos;

uniform vec2 screenSize;
uniform vec2 mousePos;

void main()
{
    vec2 dif = position.xy - mousePos;

    float len = length(dif);

    vec2 offset = vec2(0.0, 0.0);
    if (len > 0.0 && len < 100.0)
    {
        vec2 normal = dif / len;

        float coef = 1.0 - pow(len, 4.0) / pow(100.0, 4.0);

        offset = normal * 18.0 * coef;
    }

    oPos = position + offset;
    vec2 scaledPos = oPos / screenSize;
    scaledPos.y = 1.0 - scaledPos.y;
    scaledPos = scaledPos * 2.0 - vec2(1.0);

    gl_Position = vec4(scaledPos.x, scaledPos.y, 1.0, 1.0);
}
)";
    constexpr auto ps_program =
R"(
#version 330 core

in vec2 oPos;
out vec4 color;

uniform vec2 mousePos;

void main()
{
        vec2 diff = oPos - mousePos;

        float len = length(diff);

       	color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
        if (len > 0 && len < 100.0f)
        {
            float coef = 1.0 - pow(len, 2.0) / pow(100.0, 2.0);
            color.r = coef;
            color.g = 1.0 - coef;
        }
}
)";
}

GlMorphProgram::GlMorphProgram(const Engine& engine)
 : GlProgram(vs_program, ps_program)
 , _engine(engine)
 , reg(engine.eventsManager(), ext::genUniqueObjectId())
{
    _uScreenSize = glGetUniformLocation(_program, "screenSize");
    _uMousePos = glGetUniformLocation(_program, "mousePos");

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

void GlMorphProgram::activate()
{
    GlProgram::activate();

    glUniform2f(_uScreenSize, _engine.window().getWidth(), _engine.window().getHeight());

    if (_mousePos)
    {
        glUniform2f(_uMousePos, _mousePos->x, _mousePos->y);
    }
    else
    {
        glUniform2f(_uMousePos, -1.0f, -1.0f);
    }
}
