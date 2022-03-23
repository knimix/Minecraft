#pragma once
#include <unordered_map>
#include <string>
#include "../Font/Font.h"

namespace FontManager {
    void Terminate();
    void AddFont(const char* name, Font* font);
    Font* GetFont(const char* name);
};
