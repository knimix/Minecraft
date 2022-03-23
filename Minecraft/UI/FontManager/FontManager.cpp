#include "FontManager.h"
static std::unordered_map<std::string,Font*> m_Fonts;

void FontManager::Terminate() {
    std::unordered_map<std::string,Font*>::iterator it;
    for(it = m_Fonts.begin(); it != m_Fonts.end();it++){
        delete it->second;
    }
}

void FontManager::AddFont(const char *name, Font *font) {
    auto it = m_Fonts.find(name);
    if(it == m_Fonts.end()){
        m_Fonts.insert(std::make_pair(name,font));
    }
}

Font *FontManager::GetFont(const char *name) {
    auto it = m_Fonts.find(name);
    if(it != m_Fonts.end()){
        return it->second;
    }
    return nullptr;
}
