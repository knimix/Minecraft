#pragma once
#include "../../OpenGL/Buffer.h"
#include <array>
#include "glm/glm.hpp"
#include <FastNoise/FastNoise.h>
#include <atomic>
#include "Coordinate.h"


#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 255
#define CHUNK_AREA CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT


#define FACE_FRONT 0
#define FACE_BACK 1
#define FACE_LEFT 2
#define FACE_RIGHT 3
#define FACE_TOP 4
#define FACE_BOTTOM 5



class Chunk {
public:
    Chunk(int seed, const ChunkPosition& position) : m_Seed(seed), m_Position(position), m_X(position.x), m_Z(position.z){};
    void Create();
    void Delete();
    void Generate();
    void Update();
    void LoadToGPU();
    void Render();
    uint8_t GetBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z, uint8_t block);
    inline glm::vec2 GetPosition(){return {m_X,m_Z};}
    inline std::vector<int>& GetBlockData(){return m_BlockData;}
    std::atomic_bool m_Generated = false;
    std::atomic_bool m_Uploaded = false;
    std::atomic_bool m_Updating = false;
    std::atomic_bool m_FirstUpload = false;
    std::atomic_bool m_Initialized = false;
    uint8_t m_Blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    inline ChunkPosition& GetChunkPosition() {return m_Position;}
public:
    void CreateFaceData(std::vector<int>& data, uint8_t blockX, uint8_t blockY, uint8_t blockZ, uint8_t face, uint8_t blockType, uint8_t lightLevel);
    ChunkPosition m_Position;
    std::vector<int> m_BlockData;
    std::vector<int> m_BlockDataBuffer;
    int m_Seed = 0,m_X = 0, m_Z = 0;
    VertexArray* m_VertexArray = nullptr;
    ShaderBuffer* m_ShaderBuffer = nullptr;


};
