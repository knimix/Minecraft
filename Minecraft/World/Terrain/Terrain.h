#pragma once
#include "../../OpenGL/Buffer.h"
#include "../../OpenGL/Shader.h"
#include "../../UI/IO/IO.h"
#include "../Chunk/ChunkContainer/ChunkContainer.h"
#include "../../Texture/TextureMatrix.h"
#include <unordered_map>
#include <queue>

class Terrain {
public:
    Terrain(IO* io, const glm::mat4& projection, Player* player);
    ~Terrain();
    void Prepare();
    void Update();
    void Render(const glm::mat4& view);
    static std::unordered_map<uint8_t,BlockTexture> BlockTextures;
    static int ViewDistance;
private:
    Player* m_Player;
    TextureMatrix* m_TextureMatrix = nullptr;
    Shader* m_TerrainShader = nullptr;
    ChunkContainer* m_ChunkContainer;
};
