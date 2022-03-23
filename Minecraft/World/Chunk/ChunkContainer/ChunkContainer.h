#pragma once
#include "../ChunkUpdater/ChunkUpdater.h"
#include "../../../Player/Player.h"
#include "../Chunk.h"
#include "../ChunkPosition.h"
#include "../../WorldGenerator/WorldGenerator.h"
#include "../../../OpenGL/Shader.h"
#include <unordered_map>

class ChunkContainer {
public:
    ChunkContainer(Player* player, Shader* terrainShader);
    ~ChunkContainer();
    void Update();
    void Render();
    static std::unordered_map<ChunkPosition ,Chunk*,ChunkPositionHash>& GetChunks();
    static Chunk* GetChunk(const glm::vec2& position);
    static glm::vec3 ToChunkCoord(const glm::vec3& position);
    static glm::vec3 ToBlockCoord(const glm::vec3& position);
    static glm::vec3 ToLocalBlockCoord(const glm::vec3& position);
    static void SetBlock(int x, int y, int z, uint8_t block);
    static bool IsChunkInArea(Chunk* chunk, int x1, int x, int z1, int z2);
    static bool IsChunkInPlayerRange(Chunk* chunk);
    static ChunkUpdater& GetChunkProcessor(){return m_ChunkUpdater;}

private:
    static ChunkUpdater m_ChunkUpdater;
    static std::unordered_map<ChunkPosition,Chunk*,ChunkPositionHash> m_Chunks;
    static Player* m_Player;
    static ChunkUpdater* m_Updater;
    WorldGenerator m_Generator;
    Shader* m_TerrainShader;
};
