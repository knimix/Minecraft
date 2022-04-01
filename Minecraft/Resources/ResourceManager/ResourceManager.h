#pragma once
#include "../BlockManager/BlockManager.h"
#include "../TextureManager/TextureManager.h"




namespace ResourceManager{
    void Initialize();
    void Shutdown();
    TextureMatrix* GetFaceTextures();
    bool Exits(uint16_t id);
    Block& GetBlock(uint16_t id);
    uint16_t GetBlockID(const char* name);
    inline std::string GetResourceDirectory(){return "../Assets";};
}
