#pragma once

#include <cstdint>

struct BlockTexture {
    uint8_t* Front;
    uint8_t* Back;
    uint8_t* Left;
    uint8_t* Right;
    uint8_t* Top;
    uint8_t* Bottom;
};
