#include "TextureManager.h"

static TextureMatrix* s_FaceTextureMatrix = nullptr;
std::unordered_map<std::string,Texture*> s_Textures;

void TextureManager::Initialize() {
    s_FaceTextureMatrix = new TextureMatrix();
}
void TextureManager::Shutdown() {
    delete s_FaceTextureMatrix;
    for(auto texture : s_Textures){
        delete texture.second;
    }
}

bool TextureManager::LoadFaceTexture(const char *name, const char *path) {
    auto textureData = Texture::LoadTextureData(path);
    if(textureData == nullptr){
        return false;
    }
    s_FaceTextureMatrix->AddData(name,textureData);
    return true;
}
void TextureManager::CreateFaceTextureMatrix() {
    s_FaceTextureMatrix->Create(16,16,4);
}
TextureMatrix* TextureManager::GetFaceTextureMatrix() {
    return s_FaceTextureMatrix;
}
bool TextureManager::LoadTexture(const char *name, const char *path) {
    auto texture = new Texture();
    if(!texture->Load(path)){
        delete texture;
        return false;
    }
    s_Textures[name] = texture;
    return true;
}
Texture* TextureManager::GetTexture(const char *name) {
    auto it = s_Textures.find(name);
    if(it != s_Textures.end()){
        return it->second;
    }
    return nullptr;
}