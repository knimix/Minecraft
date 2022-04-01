#include "JsonLoader.h"
#include <fstream>

bool JsonLoader::LoadJason(const char *path, Json &json) {
    std::ifstream resourceFile(path);
    if(!resourceFile){
        return false;
    }
    json.clear();
    try {
        resourceFile >> json;
        return true;
    }catch(nlohmann::json::parse_error& ex){
        return false;
    }
}