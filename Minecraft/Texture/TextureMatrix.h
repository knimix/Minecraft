#pragma once
#include "BlockTexture.h"
#include <vector>

class TextureMatrix {
public:
    TextureMatrix() = default;
    ~TextureMatrix();
    void Bind();
    void AddBlockTexture(const BlockTexture& blockTexture);
    void Create(int width, int height, int mipmapLevel);

private:
    std::vector<uint8_t *> m_Textures;
    unsigned int m_Texture = 0;
    int m_Width,m_Height;
};
