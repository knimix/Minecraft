#pragma once
#include "../../Texture/TextureMatrix.h"
#include "../../Texture/Texture.h"

namespace TextureManager{
    void Initialize();
    void Shutdown();
    bool LoadFaceTexture(const char* name, const char* path);
    void CreateFaceTextureMatrix();
    TextureMatrix* GetFaceTextureMatrix();
    bool LoadTexture(const char* name, const char* path);
    Texture* GetTexture(const char* name);
}