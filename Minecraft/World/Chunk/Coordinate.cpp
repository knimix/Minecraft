#include "Coordinate.h"
#include <cmath>
#include <string>

BlockPosition Coordinate::ToBlockPosition(const glm::vec3 &position) {
    return {(int64_t) std::floor(position.x), (int64_t) std::floor(position.y), (int64_t) std::floor(position.z)};
}

BlockPosition Coordinate::ToLocalBlockPosition(const BlockPosition &blockPosition) {
    auto chunkCoord = ToChunkPosition(blockPosition);
    return {blockPosition.x - (chunkCoord.x * 16), std::clamp(blockPosition.y,(int64_t)0,(int64_t)255), blockPosition.z - (chunkCoord.z * 16)};
}

ChunkPosition Coordinate::ToChunkPosition(const BlockPosition &blockPosition) {
    return {(int64_t)std::floor((long double)blockPosition.x / 16), (int64_t)std::floor((long double)blockPosition.z / 16)};
}
uint16_t Coordinate::ToBlockIndex(const BlockPosition& blockPosition){
    auto x = std::clamp(blockPosition.x,(int64_t)0,(int64_t)15);
    auto y = std::clamp(blockPosition.y,(int64_t)0,(int64_t)255);
    auto z = std::clamp(blockPosition.z,(int64_t)0,(int64_t)15);
    return x + y * CHUNK_SIZE* CHUNK_SIZE + z * CHUNK_SIZE;
}