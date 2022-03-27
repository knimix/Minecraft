#include <iostream>
#include "WorldGenerator.h"
#include "../Chunk/ChunkMap/ChunkMap.h"
#include "../Blocks.h"


FastNoise WorldGenerator::m_Noise;

WorldGenerator::WorldGenerator() {
    m_Noise.SetFrequency(0.009);
    m_Noise.SetSeed(21321);
    m_Noise.SetFractalOctaves(8);
}


uint8_t WorldGenerator::GetDefaultBlock(int64_t x, int64_t y, int64_t z) {
   auto chunkPosition = Coordinate::ToChunkPosition({x,y,z});
    //Chunk* chunk = ChunkMap::GetChunk({chunkPosition.x,chunkPosition.z});


   float threshold = 0.55;
    auto noise = (m_Noise.GetNoise(x, y, z) + 1.0f) / 2.0f;
    if (noise < threshold)
        return BLOCK_AIR;
    else {
        if ((m_Noise.GetNoise(x, y + 1, z) + 1.0f) / 2.0f < threshold) {
            return BLOCK_GRASS;
        } else if ((m_Noise.GetNoise(x, y + 2, z) + 1.0f) / 2.0f < threshold) {
            return BLOCK_DIRT;
        } else{
            int blocktype = rand()%(1000-0 + 1) + 0;
            if(blocktype < 950){
                return BLOCK_STONE;
            }else if(blocktype < 960){
                return BLOCK_ANDESITE;
            }else if(blocktype < 980){
                return BLOCK_DIORITE;
            }else if(blocktype < 1000){
                return BLOCK_GRANITE;
            }else{
                return BLOCK_STONE;
            }

        }
    }
      /*int height = int(((m_Noise.GetNoise(x, z) + 1.0f) / 2.0f) * 30);
      if (y > height || y < 0) {
          return BLOCK_AIR;
      } else if (y == height) {
          return BLOCK_GRASS;
      } else if (y < height && y >= height - 1) {
          return BLOCK_DIRT;
      } else {
          return BLOCK_STONE;
      }*/
}



