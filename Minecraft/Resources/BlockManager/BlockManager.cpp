#include "BlockManager.h"
#include "../JsonLoader.h"
#include "../TextureManager/TextureManager.h"

std::vector<Block> s_Blocks;

void BlockManager::Initialize() {
    Block air;
    air.ID = 0;
    //air.Name = nullptr;
    air.Solid = false;
    air.Transparent = true;
    air.Transparency = 15;
    air.Faces.clear();
    s_Blocks.emplace_back(air);
}
void BlockManager::Shutdown() {
    s_Blocks.clear();
}

static uint8_t ToFaceID(const std::string& name){
    if(name == "front"){
        return FACE_FRONT;
    }
    if(name == "back"){
        return FACE_BACK;
    }
    if(name == "left"){
        return FACE_LEFT;
    }
    if(name == "right"){
        return FACE_RIGHT;
    }
    if(name == "top"){
        return FACE_TOP;
    }
    if(name == "bottom"){
        return FACE_BOTTOM;
    }
    if(name == "rotated_left"){
        return FACE_ROTATED_LEFT;
    }
    if(name == "rotated_right"){
        return FACE_ROTATED_RIGHT;
    }
    return FACE_FRONT;
}


bool BlockManager::LoadBlock(const char *path) {
    Json blockData;
    if(!JsonLoader::LoadJason(path,blockData)){
        return false;
    }
    Block block;
    auto name = blockData["name"];
    if(!name.is_null() && name.is_string()){
       // block.Name = name.get<std::string>().c_str();
    }
    auto id = blockData["id"];
    if(!id.is_null() && id.is_number_integer()){
        block.ID = id.get<uint16_t>();
    }
    auto solid = blockData["solid"];
    if(!solid.is_null() && solid.is_boolean()){
        block.Solid = solid.get<bool>();
    }
    auto transparent = blockData["transparent"];
    if(!transparent.is_null() && transparent.is_boolean()){
        block.Transparent = transparent.get<bool>();
    }
    auto transparency = blockData["transparency"];
    if(!transparency.is_null() && transparency.is_number_integer()){
        block.Transparency = transparency.get<uint8_t>();
    }
    auto faces = blockData["faces"];
    if(!faces.is_null() && faces.is_array()){
        auto faceCount = faces.size();
        Face face;
        for(int i = 0; i< faceCount;i++){
            Json faceData = blockData["faces"].at(i);
            auto type = faceData["type"];
            if(!type.is_null() && type.is_string()){
                face.FaceType = ToFaceID(type.get<std::string>());
            }
            auto texture = faceData["texture"];
            if(!texture.is_null() && texture.is_string()){
                face.Texture = TextureManager::GetFaceTextureMatrix()->GetIndex(texture.get<std::string>().c_str());
            }
            auto cull = faceData["cull"];
            if(!cull.is_null() && cull.is_boolean()){
                face.Cull = cull.get<bool>();
            }
            auto width = faceData["width"];
            if(!width.is_null() && width.is_number_unsigned()){
                face.Width = width.get<uint8_t>();
            }
            auto height = faceData["height"];
            if(!height.is_null() && height.is_number_unsigned()){
                face.Height = height.get<uint8_t>();
            }
            auto offsetX = faceData["offsetX"];
            if(!offsetX.is_null() && offsetX.is_number_integer()){
                face.OffsetX = offsetX.get<int8_t>();
            }
            auto offsetY = faceData["offsetY"];
            if(!offsetY.is_null() && offsetY.is_number_integer()){
                face.OffsetY = offsetY.get<int8_t>();
            }
            auto offsetZ = faceData["offsetZ"];
            if(!offsetZ.is_null() && offsetZ.is_number_integer()){
                face.OffsetZ = offsetZ.get<int8_t>();
            }
            block.Faces.emplace_back(face);
        }
    }
    s_Blocks.emplace_back(block);
    std::sort(s_Blocks.begin(), s_Blocks.end(),[] (const Block& node1, const Block& node2){
        return (node1.ID < node2.ID);
    });
    return true;
}
bool BlockManager::BlockExits(uint16_t id) {
    return id < s_Blocks.size();
}
Block& BlockManager::GetBlock(uint16_t id) {
    return s_Blocks[id];
}