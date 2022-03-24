#pragma once
#include "../ChunkMap/ChunkMap.h"
#include "../ChunkUpdater/ChunkUpdater.h"
#include "../../../Camera/Camera.h"

namespace ChunkManager{
    void Initialize(int seed);
    void Shutdown();
    void Update(double delaTime);
    void SetViewDistance(int distance);
    void SetCamera(Camera* camera);
    bool IsChunkInViewDistance(Chunk* chunk);
    ChunkMap* GetChunkMap();
    ChunkUpdater* GetChunkUpdater();

    bool IsChunkInArea(Chunk* chunk, int64_t x1, int64_t z1, int64_t x2, int64_t z2);
}
