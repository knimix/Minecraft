#include "Coordinate.h"
#include <cmath>
#include <string>

BlockPosition Coordinate::ToBlockPosition(const glm::vec3 &position) {
    return {(int64_t) std::floor(position.x), (int64_t) std::floor(position.y), (int64_t) std::floor(position.z)};
}

BlockPosition Coordinate::ToLocalBlockPosition(const BlockPosition &blockPosition) {
    auto chunkCoord = ToChunkPosition(blockPosition);
    return {blockPosition.x - (chunkCoord.x * CHUNK_SIZE), std::clamp(blockPosition.y,(int64_t)0,(int64_t)CHUNK_HEIGHT), blockPosition.z - (chunkCoord.z * CHUNK_SIZE)};
}

ChunkPosition Coordinate::ToChunkPosition(const BlockPosition &blockPosition) {
    return {(int64_t)std::floor((long double)blockPosition.x / CHUNK_SIZE), (int64_t)std::floor((long double)blockPosition.z / CHUNK_SIZE)};
}
uint32_t Coordinate::ToBlockIndex(const BlockPosition& blockPosition){
    auto x = std::clamp(blockPosition.x,(int64_t)0,(int64_t)CHUNK_SIZE-1);
    auto y = std::clamp(blockPosition.y,(int64_t)0,(int64_t)CHUNK_HEIGHT-1);
    auto z = std::clamp(blockPosition.z,(int64_t)0,(int64_t)CHUNK_SIZE-1);
    return x + y * (CHUNK_SIZE* CHUNK_SIZE) + z * CHUNK_SIZE;
}