#pragma once
#include <cstdint>
#include <vector>
#include <string>

#define FACE_FRONT 0
#define FACE_BACK 1
#define FACE_LEFT 2
#define FACE_RIGHT 3
#define FACE_TOP 4
#define FACE_BOTTOM 5
#define FACE_ROTATED_LEFT 6
#define FACE_ROTATED_RIGHT 7

struct Face{
    uint16_t Texture = 0;
    uint8_t Width = 16, Height = 16;
    int8_t OffsetX = 0, OffsetY = 0, OffsetZ = 0;
    bool Cull = false;
    uint8_t FaceType = FACE_FRONT;
};

struct Block{
    uint16_t ID = 0;
    bool Solid = true;
    bool Transparent = false;
    uint8_t Transparency = 0;
    std::vector<Face> Faces = {};
};

namespace BlockManager{
    void Initialize();
    void Shutdown();
    bool LoadBlock(const char* path);
    bool BlockExits(uint16_t id);
    Block& GetBlock(uint16_t id);
}