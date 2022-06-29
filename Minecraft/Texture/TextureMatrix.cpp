#include <iostream>
#include "TextureMatrix.h"
#include "../Core.h"


TextureMatrix::~TextureMatrix() {
    glDeleteTextures(1, &m_Texture);

}

void TextureMatrix::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void TextureMatrix::AddData(const char* name, uint8_t* data) {
    m_Data.insert(std::make_pair(name,data));
}

void TextureMatrix::Create(int width, int height, int mipmapLevel) {
    if(m_Data.empty()){
        return;
    }
    m_Index.clear();
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY,m_Texture);

    glTexImage3D(GL_TEXTURE_2D_ARRAY,0,GL_RGBA,width, height, m_Data.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    int index = 0;
    for (const auto& data : m_Data) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, width, height, 1,GL_RGBA, GL_UNSIGNED_BYTE,data.second);
        m_Index.insert(std::make_pair(data.first,index));
        free(data.second);
        index++;
    }
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

}

uint16_t TextureMatrix::GetIndex(const char *name) {
    auto it = m_Index.find(name);
    if(it != m_Index.end()){
        return it->second;
    }
    std::cout << name << " \n";
    return 0;
}
