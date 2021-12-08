//
// Created by Андрей Марцинкевич on 23.11.21.
//

#ifndef GAME_GLMORPHPROGRAM_HPP
#define GAME_GLMORPHPROGRAM_HPP

#include <GL/GlProgram.hpp>
#include <EventsManager.hpp>
#include <cstdint>

class Engine;
class GlMorphProgram final : public GlProgram
{
public:
    GlMorphProgram(const Engine& engine);
    void activate() override;

private:
    uint32_t _shaderProgram;

    EventsAutoRegistarator reg;

    struct MousePos
    {
        float x, y;
    };

    std::optional<MousePos> _mousePos;

    int32_t _uScreenSize;
    int32_t _uMousePos;

    const Engine& _engine;

};


#endif //GAME_GLMORPHPROGRAM_HPP
