#pragma once
#include <string>

class Texture {
public:
    Texture() = default;
    ~Texture();
    void Bind();
    inline int GetWidth(){return m_Width;}
    inline int GetHeight(){return m_Height;}
    inline unsigned int GetID(){return m_Texture;}
    bool Load(const char* path);
    static uint8_t* LoadTextureData(const char* path);

private:
    unsigned int m_Format = 0;
    int m_Width, m_Height;
    unsigned int m_Texture = 0;
};
