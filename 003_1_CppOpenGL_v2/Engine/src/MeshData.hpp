//
// Created by Андрей Марцинкевич on 22.11.21.
//

#ifndef GAME_MESHDATA_HPP
#define GAME_MESHDATA_HPP

#include <cstddef>
#include <vector>

class MeshData
{
public:
    struct Vertex
    {
        float x, y;
    };

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indexes;
};

#endif //GAME_MESHDATA_HPP
