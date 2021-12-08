//
// Created by Андрей Марцинкевич on 23.11.21.
//

#ifndef GAME_GLPROGRAM_HPP
#define GAME_GLPROGRAM_HPP

#include <ShaderProgram.hpp>
#include <cstdint>
#include <string_view>

class GlProgram : public ShaderProgram
{
public:
    GlProgram(const char* vs, const char* ps);
    ~GlProgram() override;

    virtual void activate();

protected:
    uint32_t _vertexShader;
    uint32_t _fragmentShader;
    uint32_t _program;
};

#endif //GAME_GLPROGRAM_HPP
