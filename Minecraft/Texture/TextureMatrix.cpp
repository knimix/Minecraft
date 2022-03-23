#include "TextureMatrix.h"
#include "../Core.h"
#include "Texture.h"


TextureMatrix::~TextureMatrix() {
    glDeleteTextures(1, &m_Texture);
    for(uint8_t* texture : m_Textures){
        Texture::FreeTextureData(texture);
    }
}

void TextureMatrix::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void TextureMatrix::AddBlockTexture(const BlockTexture &blockTexture) {
    m_Textures.emplace_back(blockTexture.Front);
    m_Textures.emplace_back(blockTexture.Back);
    m_Textures.emplace_back(blockTexture.Left);
    m_Textures.emplace_back(blockTexture.Right);
    m_Textures.emplace_back(blockTexture.Top);
    m_Textures.emplace_back(blockTexture.Bottom);
}

void TextureMatrix::Create(int width, int height, int mipmapLevel) {
    if(m_Textures.empty()){
        return;
    }
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY,m_Texture);

    //glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 1, 1, 1);

    glTexImage3D(GL_TEXTURE_2D_ARRAY,0,GL_RGBA,width, height, m_Textures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    for (int i = 0; i<m_Textures.size(); i++) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1,GL_RGBA, GL_UNSIGNED_BYTE,m_Textures[i]);
    }
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

}
