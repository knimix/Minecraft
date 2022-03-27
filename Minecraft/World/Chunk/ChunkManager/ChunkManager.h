#pragma once
#include "../ChunkMap/ChunkMap.h"
#include "../ChunkUpdater/ChunkUpdater.h"
#include "../ChunkGenerator/ChunkGenerator.h"
#include "../../../Camera/Camera.h"

namespace ChunkManager{
    void Initialize(int seed);
    void Shutdown();
    void Update(double delaTime);
    void SetViewDistance(int distance);
    void SetCamera(Camera* camera);
    Camera* GetCamera();
    bool IsChunkInViewDistance(Chunk* chunk);
    bool IsChunkInPreCreateDistance(Chunk* chunk);
    void SetBlock(int64_t x, int64_t y, int64_t z , uint8_t block);
    ChunkMap* GetChunkMap();
    ChunkUpdater* GetChunkUpdater();
    ChunkGenerator* GetChunkGenerator();

    bool IsChunkInArea(Chunk* chunk, int64_t x1, int64_t z1, int64_t x2, int64_t z2);
}
