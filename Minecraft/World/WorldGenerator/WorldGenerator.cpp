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
                    SetBlockAt(f,y+i,s,7);
                   // m_Blocks[ToBlockID(f, (int) y + i, s)] = 4;
                }
            }
        }
        if (i == treeHight-1) {
            for (int f = x - 1; f < x + 2; f++) {
                for (int s = z - 1; s < z + 2; s++) {
                    SetBlockAt(f,y+i,s,7);
                   // m_Blocks[ToBlockID(f, (int) y + i, s)] = 4;
                }
            }
        }
        if (i == treeHight) {
           // m_Blocks[ToBlockID(x, (int) y + i, z)] = 7;
            SetBlockAt(x,y+i,z,7);
           // m_Height.insert(std::pair<std::pair<int,int>,int>(std::pair<int,int>(x,z),y + i));
            continue;
        }
        SetBlockAt(x,y+i,z,6);
       // m_Blocks[ToBlockID(x, (int) y + i, z)] = 6;
    }



}

uint8_t WorldGenerator::GetDefaultBlock(int64_t x, int64_t y, int64_t z) {
   auto chunkPosition = Coordinate::ToChunkPosition({x,y,z});
    //Chunk* chunk = ChunkMap::GetChunk({chunkPosition.x,chunkPosition.z});

    /* float threshold = 0.55;
    auto noise = (m_Noise.GetNoise(x, y, z) + 1.0f) / 2.0f;
    if (noise < threshold)
        return 0;
    else {
        if ((m_Noise.GetNoise(x, y + 1, z) + 1.0f) / 2.0f < threshold) {
            return 1;
        } else if ((m_Noise.GetNoise(x, y + 2, z) + 1.0f) / 2.0f < threshold) {
            return 2;
        } else{
            return 3;
        }
    }*/

    float noiseValue = 1* m_Noise.GetNoise(x, z) ;
     noiseValue+= 0.5 * m_Noise.GetNoise(x * 2, z * 2);
     noiseValue+= 0.25 * m_Noise.GetNoise(x * 4, z * 4);
        noiseValue = pow(noiseValue,4.0);
        noiseValue*=60;

      int height = int((noiseValue + 1.0f) / 2.0f);

      if (y > height || y < 0) {
          return 0;
      } else if (y == height) {
          int finalNum = rand()%(1000-5+1)+5;
          if(finalNum < 100){
              SetBlockAt(x,y+1,z,4);
          }else{
              finalNum = rand()%(1000-5+1)+5;
              if(finalNum < 10){
                  PlaceTree(x,y,z);
              }else{
                  finalNum = rand()%(1000-5+1)+5;
                  if(finalNum < 40){
                      finalNum = rand()%(6-0+1)+0;
                      switch (finalNum) {
                          case 0:
                              SetBlockAt(x,y+1,z,8);
                              break;
                          case 1:
                              SetBlockAt(x,y+1,z,9);
                              break;
                          case 2:
                              SetBlockAt(x,y+1,z,10);
                              break;
                          case 3:
                              SetBlockAt(x,y+1,z,11);
                              break;
                          case 4:
                              SetBlockAt(x,y+1,z,12);
                              break;
                          case 5:
                              SetBlockAt(x,y+1,z,13);
                              break;
                      }
                  }
              }
          }
          return 1;
      } else if (y < height && y >= height - 1) {
          return 2;
      } else {
          return 3;
      }
}



