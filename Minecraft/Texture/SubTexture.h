#pragma once
#include "Texture.h"
#include "glm/vec4.hpp"

class SubTexture {
public:
    SubTexture() = default;
    SubTexture(int x, int y, int width, int height, Texture* texture) : m_X(x), m_Y(y), m_Width(width), m_Height(height), m_Texture(texture){};
    glm::vec4 GetTextureOffsets() const;
    Texture* GetTexture() const {return m_Texture;}

private:
    int m_X, m_Y, m_Width, m_Height;
    Texture* m_Texture = nullptr;
};
