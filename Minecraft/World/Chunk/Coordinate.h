#pragma once

#include <cstdint>
#include <unordered_set>
#include "glm/vec3.hpp"

struct ChunkPosition{
    int64_t x;
    int64_t z;

    bool operator==(const ChunkPosition &p) const {
        return x == p.x && z == p.z;
    }
};
struct ChunkPositionHash{
    std::size_t operator() (const ChunkPosition &position) const{
        return std::hash<int64_t>()(position.x) ^  std::hash<int64_t>()(position.z);
    }
};
struct BlockPosition{
    int64_t x;
    int64_t y;
    int64_t z;
    bool operator==(const BlockPosition &p) const {
        return x == p.x && y == p.y && z == p.z;
    }
};
struct BlockPositionHash{
    std::size_t operator() (const BlockPosition &position) const{
        return std::hash<int64_t>()(position.x) ^  std::hash<int64_t>()(position.y) ^ std::hash<int64_t>()(position.z);
    }
};

namespace Coordinate{
     BlockPosition ToBlockPosition(const glm::vec3& position);
     BlockPosition ToLocalBlockPosition(const BlockPosition& blockPosition);
     ChunkPosition ToChunkPosition(const BlockPosition& blockPosition);
}