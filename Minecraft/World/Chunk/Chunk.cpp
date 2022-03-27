#include "Chunk.h"
#include "../WorldGenerator/WorldGenerator.h"
#include "ChunkManager/ChunkManager.h"


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
                SetBlock(x, y, z, WorldGenerator::GetDefaultBlock(posX, y, posZ));
            }
        }
    }
    Generated = true;
}

void Chunk::Update() {
    m_BlockDataBuffer.clear();

    Chunk *leftChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x - 1, Position.z});
    Chunk *rightChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x + 1, Position.z});
    Chunk *frontChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x, Position.z + 1});
    Chunk *backChunk = ChunkManager::GetChunkMap()->GetChunk({Position.x, Position.z - 1});
    m_Mutex.lock();
    for (uint8_t x = 0; x < CHUNK_SIZE; x++) {
        for (uint16_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_SIZE; z++) {
                float posX = (Position.x * CHUNK_SIZE) + x;
                float posZ = (Position.z * CHUNK_SIZE) + z;
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
                        if (leftChunk->Generated) {
                            left = leftChunk->GetBlock(15, y, z);
                        }
                    }
                    right = GetBlock(x + 1, y, z);
                } else if (x == 15) {
                    right = WorldGenerator::GetDefaultBlock(posX + 1, y, posZ);
                    if (rightChunk != nullptr) {
                        if (rightChunk->Generated) {
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
                        if (backChunk->Generated) {
                            back = backChunk->GetBlock(x, y, 15);
                        }
                    }
                    front = GetBlock(x, y, z + 1);
                } else if (z == 15) {
                    front = WorldGenerator::GetDefaultBlock(posX, y, posZ + 1);
                    if (frontChunk != nullptr) {
                        if (frontChunk->Generated) {
                            front = frontChunk->GetBlock(x, y, 0);
                        }
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
                if (top == 0) {
                    CreateFaceData(m_BlockDataBuffer, x, y, z, FACE_TOP, block, 5);
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
    m_Mutex.unlock();
    Uploaded = false;
}

void Chunk::Upload() {
    if(Created){
        Uploaded = true;
        m_BlockData = m_BlockDataBuffer;
        m_ShaderBuffer->Bind();
        m_ShaderBuffer->Data(m_BlockData.data(), m_BlockData.size() * sizeof(int), GL_STATIC_DRAW);
    }
}

void Chunk::Render() {
    if(Created){
        if(!Uploaded){
            Upload();
        }
        m_VertexArray->Bind();
        m_ShaderBuffer->BindBufferBase(0);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_BlockData.size() / 2);
    }
}

void Chunk::CreateFaceData(std::vector<int> &data, uint8_t blockX, uint8_t blockY, uint8_t blockZ, uint8_t face,
                           uint8_t blockType, uint8_t lightLevel) {
    int first = (blockX << 24) | (blockY << 16) | (blockZ << 8) | (face << 0);
    int second = (blockType << 24) | (lightLevel << 16) | (0 << 8) | (0 << 0);
    data.emplace_back(first);
    data.emplace_back(second);
}

uint8_t Chunk::GetBlock(uint8_t x, uint8_t y, uint8_t z) {
    return m_Blocks[Coordinate::ToBlockIndex({x,y,z})];
}

void Chunk::SetBlock(uint8_t x, uint8_t y, uint8_t z, uint8_t block) {
    m_Blocks[Coordinate::ToBlockIndex({x,y,z})] = block;
}

