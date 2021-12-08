#include <Engine.hpp>
#include <Mesh.hpp>
#include <Renderer.hpp>

int main()
{
    Engine engine{};
    engine.init("Hello, world!", 1280, 720);

    MeshData meshData;
    for (size_t i = 200; i < 700; i+=10)
    {
        for (size_t j = 200; j < 700; j+=10)
        {
            meshData.vertices.emplace_back(MeshData::Vertex{(float)j, (float)i});
        }
    }

    for (size_t i = 0; i < 50; ++i)
    {
        for (size_t j = 0; j < 49; ++j)
        {
            meshData.indexes.emplace_back(50 * i + j);
            meshData.indexes.emplace_back(50 * i + j + 1);

            if (i != 49)
            {
                meshData.indexes.emplace_back(50 * i + j);
                meshData.indexes.emplace_back(50 * (i + 1) + j);

                if (j == 48)
                {
                    meshData.indexes.emplace_back(50 * i + j + 1);
                    meshData.indexes.emplace_back(50 * (i + 1) + j + 1);
                }
            }
        }
    }
    auto mesh = engine.renderer().createMesh(std::move(meshData), engine.renderer().createProgram("morph"));
    engine.scene()->addNode(std::move(mesh));

    while (engine.isActive())
    {
        engine.update();
    }

    return 0;
}
