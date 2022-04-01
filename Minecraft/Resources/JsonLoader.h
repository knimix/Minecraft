#pragma once
#include "Json/json.hpp"

typedef nlohmann::json Json;

namespace JsonLoader{
    bool LoadJason(const char* path, Json& json);
}