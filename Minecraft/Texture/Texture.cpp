#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "../Core.h"

Texture::~Texture() {
    glDeleteTextures(1, &m_Texture);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

bool Texture::Load(const char *path) {
    int width,height,channels;
    auto data = stbi_load(path, &width,&height,&channels,0);
    if(data == nullptr){
        return false;
    }

    m_Width = width;
    m_Height = height;

    m_Format = GL_RGB;
    if (channels == 1) {
        m_Format = GL_RED;
    } else if (channels == 3) {
        m_Format = GL_RGB;
    } else if (channels == 4) {
        m_Format = GL_RGBA;
    }

    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format,width,height, 0, m_Format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return true;
}

uint8_t *Texture::LoadTextureData(const char* path) {
    int width,height,channels;
    return stbi_load(path, &width,&height,&channels,0);
}

