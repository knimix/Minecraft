#pragma once
#include "../../OpenGL/Buffer.h"
#include "../../OpenGL/Shader.h"
#include "../../UI/IO/IO.h"
#include "../Chunk/ChunkManager/ChunkManager.h"
#include <unordered_map>
#include <queue>
#include <map>

class Terrain {
public:
    Terrain(IO* io, const glm::mat4& projection);
    ~Terrain();
    void Prepare();
    void Update(const glm::vec3& position);
    void Render(const glm::mat4& view);
    static int ViewDistance;
private:
    Shader* m_TerrainShader = nullptr;
};
