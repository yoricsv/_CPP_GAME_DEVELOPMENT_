//
// Created by Андрей Марцинкевич on 23.11.21.
//

#ifndef GAME_GLHEADERS_HPP
#define GAME_GLHEADERS_HPP

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include <string>
#include <iostream>

inline void GlCheckError(const char* file, size_t line)
{
#ifndef NDEBUG
    GLenum err(glGetError());

    while (err != GL_NO_ERROR)
    {
        std::string error;

        switch (err)
        {
            case GL_INVALID_OPERATION:error = "INVALID_OPERATION";
                break;
            case GL_INVALID_ENUM:error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:error = "INVALID_VALUE";
                break;
            case GL_OUT_OF_MEMORY:error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:error = "UNKNOWN";
                break;
        }
        std::cerr << "GL_" << error << " : 0x" << std::hex << err << std::dec << " - " << file << ":" << line
                  << std::endl;

        try
        { throw 0; }
        catch (...)
        {}


        err = glGetError();
    }

#endif

}

#endif //GAME_GLHEADERS_HPP
