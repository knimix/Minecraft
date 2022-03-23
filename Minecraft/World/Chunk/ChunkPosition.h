#pragma once
#include <utility>

typedef std::pair<int,int> ChunkPosition;

struct ChunkPositionHash{
    size_t operator()(const ChunkPosition &x)const{
        return std::hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
    }
};
