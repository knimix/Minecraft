#pragma once
#include "../Chunk/Chunk.h"
#include <FastNoise/FastNoise.h>
#include "../Chunk/ChunkPosition.h"
#include <unordered_map>

class WorldGenerator {
public:
    WorldGenerator();
   // Chunk* GenerateChunk(int chunkX,int chunkZ);
    static void GenerateChunk(Chunk* chunk);
    static uint8_t GetDefaultBlock(int64_t x, int64_t y, int64_t z);
    static int Noise3D(int64_t x, int64_t y, int64_t z);
private:
    static FastNoise m_Noise;
};
