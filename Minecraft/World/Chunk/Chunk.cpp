#include <iostream>
#include "Chunk.h"
#include "../WorldGenerator/WorldGenerator.h"
#include "ChunkManager/ChunkManager.h"


void Chunk::Create() {
    if (!m_Initialized) {
        m_VertexArray = new VertexArray();
        m_ShaderBuffer = new ShaderBuffer();
    }
    m_Initialized = true;
}

void Chunk::Delete() {
    if (m_Initialized) {
        delete m_VertexArray;
        delete m_ShaderBuffer;
    }
    m_Initialized = false;

}


void Chunk::Generate() {
    if (m_Generated) {
        return;
    }
    for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
        for (uint8_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
                float posX = (m_X * CHUNK_SIZE) + x;
                float posZ = (m_Z * CHUNK_SIZE) + z;
                SetBlock(x, y, z, WorldGenerator::GetDefaultBlock(posX, y, posZ));
            }
        }
    }
    m_Generated = true;
}


void Chunk::Update() {
    m_BlockDataBuffer.clear();
    Chunk *leftChunk = ChunkManager::GetChunkMap()->GetChunk({m_X - 1, m_Z});
    Chunk *rightChunk = ChunkManager::GetChunkMap()->GetChunk({m_X + 1, m_Z});
    Chunk *frontChunk = ChunkManager::GetChunkMap()->GetChunk({m_X, m_Z + 1});
    Chunk *backChunk = ChunkManager::GetChunkMap()->GetChunk({m_X, m_Z - 1});

    // Chunk *leftChunk = nullptr;
    // Chunk *rightChunk = nullptr;
    //  Chunk *frontChunk = nullptr;
    //  Chunk *backChunk = nullptr;

    for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
        for (uint8_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
                float posX = (m_X * CHUNK_SIZE) + x;
                float posZ = (m_Z * CHUNK_SIZE) + z;
                uint8_t block = GetBlock(x, y, z);

                if (block == 0) {
                    continue;
                }

                uint8_t right = 1;
                uint8_t left = 1;
                uint8_t front = 1;
                uint8_t back = 1;
                uint8_t top = 1;
                uint8_t bottom = 1;

                if (x == 0) {
                    left = WorldGenerator::GetDefaultBlock(posX - 1, y, posZ);
                    if (leftChunk != nullptr) {
                        if (leftChunk->m_Generated) {
                            left = leftChunk->GetBlock(15, y, z);
                        }
                    }
                    right = GetBlock(x + 1, y, z);
                } else if (x == 15) {
                    right = WorldGenerator::GetDefaultBlock(posX + 1, y, posZ);
                    if (rightChunk != nullptr) {
                        if (rightChunk->m_Generated) {
                            right = rightChunk->GetBlock(0, y, z);
                        }
                    }
                    left = GetBlock(x - 1, y, z);
                } else {
                    right = GetBlock(x + 1, y, z);
                    left = GetBlock(x - 1, y, z);
                }

                if (z == 0) {
                    back = WorldGenerator::GetDefaultBlock(posX, y, posZ - 1);
                    if (backChunk != nullptr) {
                        if (backChunk->m_Generated) {
                            back = backChunk->GetBlock(x, y, 15);
                        }
                    }
                    front = GetBlock(x, y, z + 1);
                } else if (z == 15) {
                    front = WorldGenerator::GetDefaultBlock(posX, y, posZ + 1);
                    if (frontChunk != nullptr) {
                        if (frontChunk->m_Generated) {
                            front = frontChunk->GetBlock(x, y, 0);
                        }
                    }
                    back = GetBlock(x, y, z - 1);
                } else {
                    front = GetBlock(x, y, z + 1);
                    back = GetBlock(x, y, z - 1);
                    // back = WorldGenerator::GetDefaultBlock(posX,y,posZ-1);
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
                if (top == 0) {
                    if(x == 15 || x == 0 || z == 0 || z == 15){
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_TOP, 3, 5);
                    }else{
                        CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_TOP, block, 5);

                    }
                }
                if (bottom == 0) {
                    CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_BOTTOM, block, 5);
                }
                if (left == 0) {
                    CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_LEFT, block, 5);
                }
                if (right == 0) {
                    CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_RIGHT, block, 5);
                }
                if (front == 0) {
                    CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_FRONT, block, 5);
                }
                if (back == 0) {
                    CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_BACK, block, 5);
                }
            }
        }
    }
    m_Uploaded = false;

}

void Chunk::LoadToGPU() {
    m_BlockData = m_BlockDataBuffer;
    m_VertexArray->Bind();
    m_ShaderBuffer->Data(m_BlockData.data(), m_BlockData.size() * sizeof(int), GL_STATIC_DRAW);
    m_Uploaded = true;
}

void Chunk::Render() {
    if (m_Initialized) {
        if (!m_Uploaded && !m_Updating) {
            LoadToGPU();
        }
        m_VertexArray->Bind();
        m_ShaderBuffer->BindBufferBase(0);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_BlockData.size() / 2);
    }

}

uint8_t Chunk::GetBlock(int x, int y, int z) {
    return m_Blocks[x][y][z];
}

void Chunk::SetBlock(int x, int y, int z, uint8_t block) {
    m_Blocks[x][y][z] = block;
}

void Chunk::CreateFaceData(std::vector<int> &data, uint8_t blockX, uint8_t blockY, uint8_t blockZ, uint8_t face,
                           uint8_t blockType, uint8_t lightLevel) {
    int first = (blockX << 24) | (blockY << 16) | (blockZ << 8) | (face << 0);
    int second = (blockType << 24) | (lightLevel << 16) | (0 << 8) | (0 << 0);
    data.emplace_back(first);
    data.emplace_back(second);

}










