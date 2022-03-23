#pragma once
#include <string>

class Texture {
public:
    explicit Texture(const std::string& path);
    ~Texture();
    void Bind();
    inline int GetWidth(){return m_Width;}
    inline int GetHeight(){return m_Height;}
    inline unsigned int GetID(){return m_Texture;}
    static uint8_t* LoadTexture(const char* path);
    static void FreeTextureData(uint8_t* data);

private:
    int m_Width, m_Height;
    unsigned int m_Texture = 0;
};
