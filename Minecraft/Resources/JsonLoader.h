#pragma once
#include <Json/json.hpp>
#include "../Core.h"

typedef nlohmann::json Json;

namespace JsonLoader{
    bool LoadJason(const char* path, Json& json);
    bool CreateJson(const char* path, const Json& json);
}