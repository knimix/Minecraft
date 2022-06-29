#pragma once
#include <vector>
#include <stdint.h>

namespace ChunkMeshGenerator {
    void GenerateMesh(std::vector<uint8_t>& m_BlockData,std::vector<int>& culledFaces, std::vector<int>& nonCulledFaces);
};
