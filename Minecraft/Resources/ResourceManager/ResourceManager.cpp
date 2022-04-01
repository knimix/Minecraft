#include "ResourceManager.h"
#include "../JsonLoader.h"
#include <string>
#include <iostream>


void ResourceManager::Initialize() {
    TextureManager::Initialize();
    BlockManager::Initialize();
    std::cout << "Loading resources...\n";

    Json resources;
    if (!JsonLoader::LoadJason(std::string(GetResourceDirectory() + "/resources.json").c_str(), resources)) {
        std::cerr << "Failed to load resources: file corrupted!\n";
    }
    for (const auto &faceTexture: resources["FaceTextures"].items()) {
        std::string path = faceTexture.value();
        std::string name = faceTexture.key();
        if (!TextureManager::LoadFaceTexture(name.c_str(), std::string(GetResourceDirectory() + "/textures/blocks/" + path).c_str())) {
            std::cerr << "Failed to load resources: " << path << "\n";
        }
    }
    std::cout << "Loaded " << resources["FaceTextures"].size() << " face textures!\n";
    TextureManager::CreateFaceTextureMatrix();

    for (const auto &blockModel: resources["BlockModels"]) {
        std::string path = "models/" + blockModel.get<std::string>();
        if (!BlockManager::LoadBlock(std::string(GetResourceDirectory() + "/" + path).c_str())) {
            std::cerr << "Failed to load resources: " << path << "\n";
        }
    }
    std::cout << "Loaded " << resources["BlockModels"].size() << " block models!\n";
}

void ResourceManager::Shutdown() {
    TextureManager::Shutdown();
    BlockManager::Shutdown();
}

