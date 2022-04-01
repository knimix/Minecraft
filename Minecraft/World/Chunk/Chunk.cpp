#include "Chunk.h"
#include "../WorldGenerator/WorldGenerator.h"
#include "ChunkManager/ChunkManager.h"
#include "../../Resources/BlockManager/BlockManager.h"
#include <iostream>
#include <bitset>


void Chunk::Create() {
    m_VertexArray = new VertexArray();
    m_ShaderBuffer = new ShaderBuffer();
    Created = true;
}

void Chunk::Destroy() {
    delete m_VertexArray;
    delete m_ShaderBuffer;
    Created = false;
    FirstUpdate = false;
}

void Chunk::Generate() {
    for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
        for (uint16_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
                int64_t posX = (Position.x * CHUNK_SIZE) + x;
                int64_t posZ = (Position.z * CHUNK_SIZE) + z;
                if (GetBlock(x, y, z) == 0) {
                    SetBlock(x, y, z, WorldGenerator::GetDefaultBlock(posX, y, posZ));
                }
            }
        }
    }
    Generated = true;
}

void Chunk::Update() {
    m_BlockDataBuffer.clear();

    Chunk *leftChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x - 1, Position.z}, true);
    Chunk *rightChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x + 1, Position.z}, true);
    Chunk *frontChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x, Position.z + 1}, true);
    Chunk *backChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x, Position.z - 1}, true);
    m_Mutex.lock();
    for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
        for (uint16_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
                uint8_t block = GetBlock(x, y, z);
                if(block == 0){
                    continue;
                }

                if(!BlockManager::BlockExits(block)){
                    continue;
                }
                auto blockData = BlockManager::GetBlock(block);


                uint8_t right = 1;
                uint8_t left = 1;
                uint8_t front = 1;
                uint8_t back = 1;
                uint8_t top = 1;
                uint8_t bottom = 1;

                if (x == 0) {
                    if (leftChunk != nullptr) {
                        left = leftChunk->GetBlock(15, y, z);

                    }
                    right = GetBlock(x + 1, y, z);
                } else if (x == 15) {
                    if (rightChunk != nullptr) {
                        right = rightChunk->GetBlock(0, y, z);

                    }
                    left = GetBlock(x - 1, y, z);
                } else {
                    right = GetBlock(x + 1, y, z);
                    left = GetBlock(x - 1, y, z);
                }

                if (z == 0) {
                    if (backChunk != nullptr) {
                        back = backChunk->GetBlock(x, y, 15);

                    }
                    front = GetBlock(x, y, z + 1);
                } else if (z == 15) {
                    if (frontChunk != nullptr) {
                        front = frontChunk->GetBlock(x, y, 0);

                    }
                    back = GetBlock(x, y, z - 1);
                } else {
                    front = GetBlock(x, y, z + 1);
                    back = GetBlock(x, y, z - 1);
                }

                if (y == 0) {
                    top = GetBlock(x, y + 1, z);
                    bottom = 0;
                } else if (y == 255) {
                    bottom = GetBlock(x, y - 1, z);
                    top = 0;
                } else {
                    bottom = GetBlock(x, y - 1, z);
                    top = GetBlock(x, y + 1, z);
                }

                for (auto &face: blockData.Faces) {

                    if (top == 0 && face.FaceType == FACE_TOP) {
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_TOP, 0, face.Texture,face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);
                    }
                    if (bottom == 0 && face.FaceType == FACE_BOTTOM) {
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_BOTTOM, 0, face.Texture, face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);
                    }
                    if (left == 0 && face.FaceType == FACE_LEFT) {
                        CreateFaceData(m_BlockDataBuffer, x, y, z,  FACE_LEFT, 0, face.Texture, face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);
                    }
                    if (right == 0 && face.FaceType == FACE_RIGHT) {
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_RIGHT, 0, face.Texture, face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);
                    }
                    if (front == 0 && face.FaceType == FACE_FRONT) {
                        CreateFaceData(m_BlockDataBuffer, x, y, z , FACE_FRONT, 0, face.Texture , face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);
                    }
                    if (back == 0 && face.FaceType == FACE_BACK) {
                        CreateFaceData(m_BlockDataBuffer, x, y, z,FACE_BACK, 0, face.Texture, face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);
                    }
                    if(face.FaceType == FACE_ROTATED_LEFT){
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_ROTATED_LEFT, 0, face.Texture, face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);

                    }
                    if(face.FaceType == FACE_ROTATED_RIGHT){
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_ROTATED_RIGHT, 0, face.Texture, face.OffsetX, face.OffsetY,face.OffsetZ, face.Width, face.Height);

                    }
                }


            }
        }
    }
    ChunkManager::GetChunkMap()->UnlockChunk(leftChunk);
    ChunkManager::GetChunkMap()->UnlockChunk(rightChunk);
    ChunkManager::GetChunkMap()->UnlockChunk(frontChunk);
    ChunkManager::GetChunkMap()->UnlockChunk(backChunk);
    m_Mutex.unlock();
    Uploaded = false;
}

void Chunk::Upload() {
    if (Created) {
        Uploaded = true;
        m_BlockData = m_BlockDataBuffer;
        m_ShaderBuffer->Bind();
        m_ShaderBuffer->Data(m_BlockData.data(), m_BlockData.size() * sizeof(int), GL_STATIC_DRAW);
    }
}

void Chunk::Render() {
    if (Created) {
        if (!Uploaded) {
            Upload();
        }
        m_VertexArray->Bind();
        m_ShaderBuffer->BindBufferBase(0);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_BlockData.size() / 3);
    }
}


void Chunk::CreateFaceData(std::vector<int>& data, uint8_t blockX, uint8_t blockY, uint8_t blockZ, uint8_t faceType, uint8_t lightLevel, uint16_t textureIndex,  int8_t offsetX, int8_t offsetY, int8_t offsetZ,uint8_t width, uint8_t height) {

    int first = (blockX << 24) | (blockY << 16) | (blockZ << 8) | (faceType << 4) | (lightLevel << 0) ;
    int second = (textureIndex << 24) | (width << 16) | (height << 8) | (0 << 0);




    using U = std::uint8_t;
    int third  = (U(offsetX) << 24) | (U(offsetY) << 16) | (U(offsetZ) << 8) | (0 << 0);
   // std::cout << (int)(third & 0xFF000000 >> 24) << " "<< (int)(third  & 0x00FF0000 >> 16 )<< " " << (int)(third & 0x0000FF00 >> 8)  << std::endl;

    data.emplace_back(first);
    data.emplace_back(second);
    data.emplace_back(third);

}

uint8_t Chunk::GetBlock(uint8_t x, uint8_t y, uint8_t z) {
    return m_Blocks[Coordinate::ToBlockIndex({x, y, z})];
}

void Chunk::SetBlock(uint8_t x, uint8_t y, uint8_t z, uint8_t block) {
    m_Blocks[Coordinate::ToBlockIndex({x, y, z})] = block;
}

bool Chunk::NeighboursGenerated() {
    Chunk *leftChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x - 1, Position.z});
    Chunk *rightChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x + 1, Position.z});
    Chunk *frontChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x, Position.z + 1});
    Chunk *backChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x, Position.z - 1});
    if (leftChunk == nullptr || rightChunk == nullptr || frontChunk == nullptr || backChunk == nullptr) {
        return false;
    }
    return leftChunk->Generated && rightChunk->Generated && frontChunk->Generated && backChunk->Generated;
}


