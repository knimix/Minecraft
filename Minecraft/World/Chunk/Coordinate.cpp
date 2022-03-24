#include "Coordinate.h"
#include <cmath>

BlockPosition Coordinate::ToBlockPosition(const glm::vec3 &position) {
    return {(int64_t) std::floor(position.x), (int64_t) std::floor(position.y), (int64_t) std::floor(position.z)};
}

BlockPosition Coordinate::ToLocalBlockPosition(const BlockPosition &blockPosition) {
    auto chunkCoord = ToChunkPosition(blockPosition);
    return {blockPosition.x - (chunkCoord.x * 16), blockPosition.y, blockPosition.z - (chunkCoord.z * 16)};
}

ChunkPosition Coordinate::ToChunkPosition(const BlockPosition &blockPosition) {
    return {(int64_t)std::floor((long double)blockPosition.x / 16), (int64_t)std::floor((long double)blockPosition.z / 16)};
}
