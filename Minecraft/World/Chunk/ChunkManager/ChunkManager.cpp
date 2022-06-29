#include "ChunkManager.h"
#include <iostream>

static ChunkMap *s_ChunkMap = nullptr;
static ChunkUpdater *s_ChunkUpdater = nullptr;
static ChunkGenerator *s_ChunkGenerator = nullptr;
static int s_ViewDistance = 18;
static int s_PreCreateDistance = 1;
static int s_Seed = 33;
static Camera *s_Camera = nullptr;


void PreCreateChunks(const ChunkPosition &center) {
    for (int64_t x = center.x - s_ViewDistance - s_PreCreateDistance;
         x <= center.x + s_ViewDistance + s_PreCreateDistance; x++) {
        for (int64_t z = center.z - s_ViewDistance - s_PreCreateDistance;
             z <= center.z + s_ViewDistance + s_PreCreateDistance; z++) {
            auto chunkPosition = ChunkPosition{x, z};
            if (!s_ChunkMap->ChunkExist(chunkPosition)) {
                auto chunk = new Chunk(chunkPosition);
                s_ChunkMap->AddChunk(chunk, chunkPosition);
                ChunkGenerator::GenerateChunk(chunk);
            }
        }
    }
}




void ChunkManager::Initialize(int seed) {
    s_ChunkMap = new ChunkMap();
    s_ChunkUpdater = new ChunkUpdater(1);
    s_ChunkGenerator = new ChunkGenerator(5);
    s_Seed = seed;
}

void ChunkManager::Shutdown() {
    delete s_ChunkMap;
    delete s_ChunkUpdater;
}

void ChunkManager::Update(double delaTime) {
    auto chunkPosition = Coordinate::ToChunkPosition(Coordinate::ToBlockPosition(s_Camera->GetCameraPosition()));

    PreCreateChunks(chunkPosition);

    for(auto chunk : s_ChunkMap->GetChunks()){
        if(IsChunkInViewDistance(chunk)){
            if(!chunk->Created){
                chunk->Create();
            }else{
                if(chunk->Generated && chunk->NeighboursGenerated() && !chunk->FirstUpdate){
                    chunk->FirstUpdate = true;
                    ChunkUpdater::UpdateChunk(chunk);
                }
            }
        }else{
            if(chunk->Created){
                chunk->Destroy();
            }
        }

        if(!IsChunkInPreCreateDistance(chunk)){
            if(!chunk->Updating && !chunk->Generating && !chunk->Accessed){
                s_ChunkMap->RemoveChunk(chunk->Position);
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

Camera *ChunkManager::GetCamera() {
    return s_Camera;
}

bool ChunkManager::IsChunkInViewDistance(Chunk *chunk) {
    auto playerPosition = Coordinate::ToChunkPosition(Coordinate::ToBlockPosition(s_Camera->GetCameraPosition()));
    return IsChunkInArea(chunk, playerPosition.x - s_ViewDistance, playerPosition.z - s_ViewDistance,
                         playerPosition.x + s_ViewDistance, playerPosition.z + s_ViewDistance);
}

bool ChunkManager::IsChunkInPreCreateDistance(Chunk *chunk) {
    auto playerPosition = Coordinate::ToChunkPosition(Coordinate::ToBlockPosition(s_Camera->GetCameraPosition()));
    return IsChunkInArea(chunk, playerPosition.x - (s_ViewDistance + s_PreCreateDistance),
                         playerPosition.z - (s_ViewDistance + s_PreCreateDistance),
                         playerPosition.x + (s_ViewDistance + s_PreCreateDistance),
                         playerPosition.z + (s_ViewDistance + s_PreCreateDistance));
}

void ChunkManager::SetBlock(int64_t x, int64_t y, int64_t z, uint8_t block) {
    auto chunk = GetChunkMap()->GetChunk(Coordinate::ToChunkPosition({x, y, z}));
    if (chunk == nullptr) {
        return;
    }
    auto blockCoord = Coordinate::ToLocalBlockPosition({x, y, z});
    chunk->SetBlock(blockCoord.x, blockCoord.y, blockCoord.z, block);
    ChunkUpdater::UpdateChunk(chunk);
}

ChunkMap *ChunkManager::GetChunkMap() {
    return s_ChunkMap;
}

ChunkUpdater *ChunkManager::GetChunkUpdater() {
    return s_ChunkUpdater;
}
ChunkGenerator* ChunkManager::GetChunkGenerator() {
    return s_ChunkGenerator;
}
bool ChunkManager::IsChunkInArea(Chunk *chunk, int64_t x1, int64_t z1, int64_t x2, int64_t z2) {
    if (chunk == nullptr) {
        return false;
    }
    return chunk->Position.x >= x1 && chunk->Position.x <= x2 &&
           chunk->Position.z >= z1 && chunk->Position.z <= z2;
}
