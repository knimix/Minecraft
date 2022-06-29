#include "JsonLoader.h"
#include <fstream>


bool JsonLoader::LoadJason(const char *path, Json &json) {
    json.clear();
    std::ifstream file(path);
    try {
        file >> json;
        return true;
    }catch(nlohmann::json::parse_error& ex){
        return false;
    }
}
bool JsonLoader::CreateJson(const char* path,const Json& json){
    std::ofstream file(path);
    if(!file){
        return false;
    }
    try {
        file << std::setw(4) << json;
        file.close();
        return true;
    }catch(nlohmann::json::parse_error& ex){
        file.close();
        return false;
    }
}