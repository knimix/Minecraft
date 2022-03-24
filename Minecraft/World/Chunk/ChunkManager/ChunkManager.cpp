#include "ChunkManager.h"
#include <iostream>

static ChunkMap* s_ChunkMap = nullptr;
static ChunkUpdater* s_ChunkUpdater = nullptr;
static int s_ViewDistance = 12;
static int s_Seed = 99;
static Camera* s_Camera = nullptr;




void ChunkManager::Initialize(int seed) {
    s_ChunkMap = new ChunkMap();
    s_ChunkUpdater = new ChunkUpdater(4);
    s_Seed = seed;
}
void ChunkManager::Shutdown() {
    delete s_ChunkMap;
    delete s_ChunkUpdater;
}
void ChunkManager::Update(double delaTime) {
    auto chunkPosition = Coordinate::ToChunkPosition(Coordinate::ToBlockPosition(s_Camera->GetCameraPosition()));
    for(int64_t x = chunkPosition.x -s_ViewDistance; x <= chunkPosition.x + s_ViewDistance ;x++){
        for(int64_t z = chunkPosition.z -s_ViewDistance; z <= chunkPosition.z +s_ViewDistance ;z++){
            auto currentChunkPosition = ChunkPosition{x,z};
            if(!s_ChunkMap->ChunkExist(currentChunkPosition)){
                auto chunk = new Chunk(s_Seed,currentChunkPosition);
                chunk->Create();
                s_ChunkMap->AddChunk(chunk,currentChunkPosition);
                s_ChunkUpdater->UpdateChunk(chunk);}
        }
    }
    for(auto chunk : s_ChunkMap->GetChunks()){
        if(!IsChunkInViewDistance(chunk)){
            if(!chunk->m_Updating && chunk->m_Generated){
                chunk->Delete();
                s_ChunkMap->RemoveChunk(chunk->GetChunkPosition());
                delete chunk;
            }
        }
    }

}
void ChunkManager::SetViewDistance(int distance) {
    s_ViewDistance = distance;
}
void ChunkManager::SetCamera(Camera *camera) {
    s_Camera = camera;
}
bool ChunkManager::IsChunkInViewDistance(Chunk *chunk) {
    auto playerPosition = Coordinate::ToChunkPosition(Coordinate::ToBlockPosition(s_Camera->GetCameraPosition()));
    return IsChunkInArea(chunk,playerPosition.x -s_ViewDistance,playerPosition.z -s_ViewDistance,playerPosition.x + s_ViewDistance,playerPosition.z + s_ViewDistance);
}
ChunkMap* ChunkManager::GetChunkMap() {
    return s_ChunkMap;
}
ChunkUpdater* ChunkManager::GetChunkUpdater() {
    return s_ChunkUpdater;
}

bool ChunkManager::IsChunkInArea(Chunk *chunk, int64_t x1, int64_t z1, int64_t x2, int64_t z2) {
    if(chunk == nullptr){
        return false;
    }
    return chunk->GetChunkPosition().x >= x1 && chunk->GetChunkPosition().x <= x2 && chunk->GetChunkPosition().z >= z1 && chunk->GetChunkPosition().z <= z2;
}
