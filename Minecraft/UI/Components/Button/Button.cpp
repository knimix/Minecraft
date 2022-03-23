#include "Button.h"

void Button::Update(IO *io, double deltaTime) {
    Component::Update(io, deltaTime);
    if(io->MouseX >= m_Position.x && io->MouseX <= m_Position.x + m_Size.x && io->MouseY >= m_Position.y && io->MouseY <= m_Position.y + m_Size.y){
        if(m_CurrentColor != m_HoverColor){
            m_CurrentColor = m_HoverColor;
        }
        if(io->MouseClicked[GLFW_MOUSE_BUTTON_1]){
            if(m_ClickCallback != nullptr){
                m_ClickCallback();
            }
        }
    }else{
        if(m_CurrentColor != m_Color){
            m_CurrentColor = m_Color;
        }
    }
}

void Button::Render(Renderer2D *renderer) {
    Component::Render(renderer);
    if(m_Texture != nullptr){
        renderer->DrawQuad(m_Position,m_Size,m_CurrentColor,m_Texture);
    }else if(m_SubTexture.GetTexture() != nullptr){
        renderer->DrawQuad(m_Position,m_Size,m_CurrentColor, m_SubTexture);
    }else{
        renderer->DrawQuad(m_Position,m_Size,m_CurrentColor);
    }
    if(!m_Text.empty()){
        renderer->DrawString(m_Text.c_str(),m_Font,m_Position,m_Size,m_TextColor);
    }

}
