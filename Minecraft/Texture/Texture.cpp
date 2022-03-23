#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "../Core.h"

Texture::Texture(const std::string &path) {
    int width,height,channels;
    uint8_t* textureData = stbi_load(path.c_str(), &width,&height,&channels,0);
    m_Width = width;
    m_Height = height;
    auto format = GL_RGB;
    if (channels == 1) {
        format = GL_RED;
    } else if (channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    }
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, format,width,height, 0, format, GL_UNSIGNED_BYTE, textureData);
    stbi_image_free(textureData);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_Texture);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

uint8_t *Texture::LoadTexture(const char *path) {
    int width,height,channels;

    return stbi_load(path, &width,&height,&channels,0);
}

void Texture::FreeTextureData(uint8_t *data) {
    stbi_image_free(data);
}
