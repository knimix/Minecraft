#include "ChunkMeshGenerator.h"
#include "../../Coordinate.h"
#include "../../../Resources/BlockManager/BlockManager.h"

void ChunkMeshGenerator::GenerateMesh(std::vector<uint8_t> &blockData, std::vector<int> &culledFaces,
                                      std::vector<int> &nonCulledFaces) {
    culledFaces.clear();
    nonCulledFaces.clear();

    for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
        for (uint16_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
                auto currentBlockID = blockData[Coordinate::ToBlockIndex({x,y,z})];
                if(currentBlockID == 0){
                    continue;
                }
                if(!BlockManager::BlockExits(currentBlockID)){
                    continue;
                }
                const Block& currentBlockData = BlockManager::GetBlock(currentBlockID);

                uint8_t rightBlockID;
                uint8_t leftBlockID;
                uint8_t frontBlockID;
                uint8_t backBlockID;
                uint8_t topBlockID;
                uint8_t bottomBlockID;


            }
        }
    }
}