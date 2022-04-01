#pragma once
#include "BlockTexture.h"
#include <unordered_map>
#include <string>

class TextureMatrix {
public:
    TextureMatrix() = default;
    ~TextureMatrix();
    void Bind();
    void AddData(const char* name, uint8_t* data);
    void Create(int width, int height, int mipmapLevel);
    uint16_t GetIndex(const char* name);

private:
    std::unordered_map<std::string,uint8_t*> m_Data;
    std::unordered_map<std::string,int> m_Index;
    unsigned int m_Texture = 0;
    int m_Width,m_Height;
};
