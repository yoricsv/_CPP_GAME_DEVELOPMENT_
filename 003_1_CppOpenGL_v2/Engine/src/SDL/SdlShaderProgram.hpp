//
// Created by Андрей Марцинкевич on 21.11.21.
//

#ifndef GAME_SDLSHADERPROGRAM_HPP
#define GAME_SDLSHADERPROGRAM_HPP

#include <ShaderProgram.hpp>
#include <MeshData.hpp>

#include <cstdint>
#include <cstddef>

class SdlShaderProgram : public ShaderProgram
{
public:
    virtual void applyVertex(MeshData::Vertex& vertex) = 0;

    struct Pixel
    {
        uint8_t r = 0, g = 0, b = 0;
    };

    virtual Pixel getPixel(size_t x, size_t y) = 0;
};

#endif //GAME_SDLSHADERPROGRAM_HPP
