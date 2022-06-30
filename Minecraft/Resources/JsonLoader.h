#pragma once
#ifdef WIN32
#include <Json/json.hpp>
#else
#include <nlohmann/json.hpp>
#endif
#include "../Core.h"

typedef nlohmann::json Json;

namespace JsonLoader{
    bool LoadJason(const char* path, Json& json);
    bool CreateJson(const char* path, const Json& json);
}