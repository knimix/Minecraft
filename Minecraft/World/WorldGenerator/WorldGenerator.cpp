#include <iostream>
#include "WorldGenerator.h"
#include "../Chunk/ChunkMap/ChunkMap.h"
#include "../Chunk/ChunkManager/ChunkManager.h"
#include <vector>


FastNoise WorldGenerator::m_Noise;

WorldGenerator::WorldGenerator() {
    m_Noise.SetFrequency(0.009);
    m_Noise.SetSeed(21321);
    m_Noise.SetFractalOctaves(8);
}

void SetBlockAt(int64_t x, int64_t y, int64_t z, uint8_t block){
    auto chunkPosition = Coordinate::ToChunkPosition({x,y,z});
    Chunk* chunk = ChunkManager::GetChunkMap()->GetChunk(chunkPosition,true);

    auto localPosition = Coordinate::ToLocalBlockPosition({x,y,z});
    if(chunk != nullptr){
        chunk->SetBlock(localPosition.x, localPosition.y,localPosition.z,block);
    }
    ChunkManager::GetChunkMap()->UnlockChunk(chunk);
}

void PlaceTree(int64_t x, int64_t y, int64_t z){


    int treeHight = rand() % (8 - 6 + 1) + 6;
    for (int i = 0; i <= treeHight; i++) {
        if (i == treeHight-3 || i == treeHight-2) {
            for (int f = x - 2; f < x + 3; f++) {
                for (int s = z - 2; s < z + 3; s++) {
                    SetBlockAt(f,y+i,s,10);
                   // m_Blocks[ToBlockID(f, (int) y + i, s)] = 4;
                }
            }
        }
        if (i == treeHight-1) {
            for (int f = x - 1; f < x + 2; f++) {
                for (int s = z - 1; s < z + 2; s++) {
                    SetBlockAt(f,y+i,s,10);
                   // m_Blocks[ToBlockID(f, (int) y + i, s)] = 4;
                }
            }
        }
        if (i == treeHight) {
           // m_Blocks[ToBlockID(x, (int) y + i, z)] = 4;
            SetBlockAt(x,y+i,z,10);
           // m_Height.insert(std::pair<std::pair<int,int>,int>(std::pair<int,int>(x,z),y + i));
            continue;
        }
        SetBlockAt(x,y+i,z,9);
       // m_Blocks[ToBlockID(x, (int) y + i, z)] = 3;
    }



}

uint8_t WorldGenerator::GetDefaultBlock(int64_t x, int64_t y, int64_t z) {
   auto chunkPosition = Coordinate::ToChunkPosition({x,y,z});
    //Chunk* chunk = ChunkMap::GetChunk({chunkPosition.x,chunkPosition.z});


/*  float threshold = 0.55;
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
    }*/
      int height = int(((m_Noise.GetNoise(x, z) + 1.0f) / 2.0f) * 60);

      if(y == height){
          int randNum = rand()%(1000-0 + 1) + 0;
          if(randNum <= 9){
             // PlaceTree(x,y,z);

          }else{
              randNum = rand()%(1000-0 + 1) + 0;
              if(randNum <= 50){
                //  SetBlockAt(x,y+1,z,11);
              }else{
                  randNum = rand()%(1000-0 + 1) + 0;
                  if(randNum <= 100){
                     // SetBlockAt(x,y+1,z,12);
                  }
              }
          }
      }

      if (y > height || y < 0) {
          return 0;
      } else if (y == height) {
          return 1;
      } else if (y < height && y >= height - 1) {
          return 2;
      } else {
          return 3;
      }
}



