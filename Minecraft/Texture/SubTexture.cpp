#include <iostream>
#include "SubTexture.h"

static float Map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

glm::vec4 SubTexture::GetTextureOffsets() const{
    if(m_Texture == nullptr){
        return {0,0,0,0};
    }
    glm::vec4 offsets;
    offsets.x = Map(m_X,0,m_Texture->GetWidth(),0.0,1.0);
    offsets.y = Map(m_Y,0,m_Texture->GetHeight(),0.0,1.0);
    offsets.z = Map(m_Width,0,m_Texture->GetWidth(),0.0,1.0);
    offsets.w = Map(m_Height,0,m_Texture->GetHeight(),0.0,1.0);
    return offsets;
}
