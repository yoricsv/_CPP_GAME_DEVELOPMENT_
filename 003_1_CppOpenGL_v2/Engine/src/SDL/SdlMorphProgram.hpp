//
// Created by Андрей Марцинкевич on 21.11.21.
//

#ifndef GAME_SDLMORPHPROGRAM_HPP
#define GAME_SDLMORPHPROGRAM_HPP

#include <SDL/SdlShaderProgram.hpp>
#include <EventsManager.hpp>

#include <optional>

class Engine;

class SdlMorphProgram final : public SdlShaderProgram
{
public:
    explicit SdlMorphProgram(const Engine& engine);

    void applyVertex(MeshData::Vertex &vertex) override;

    Pixel getPixel(size_t x, size_t y) override;

private:
    EventsAutoRegistarator reg;

    struct MousePos
    {
        size_t x, y;
    };

    std::optional<MousePos> _mousePos;
};


#endif //GAME_SDLMORPHPROGRAM_HPP
