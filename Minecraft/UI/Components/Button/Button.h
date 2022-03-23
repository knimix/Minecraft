#pragma once
#include "../Component.h"

class Button : public Component{
public:
    Button() = default;
    void Update(IO* io, double deltaTime) override;
    void Render(Renderer2D* renderer) override;
    inline void SetPosition(const glm::vec2& position){m_Position = position;}
    inline void SetSize(const glm::vec2& size){m_Size = size;}
    inline void SetColor(const glm::vec4& color){m_Color = color; m_CurrentColor = color;}
    inline void SetHover(const glm::vec4& color){m_HoverColor = color;}
    inline void SetTexture(Texture* texture){m_Texture = texture;}
    inline void SetSubTexture(const SubTexture& subTexture){m_SubTexture = subTexture;}
    inline void SetFont(Font* font){m_Font = font;}
    inline void SetText(const char* text){m_Text = text;}
    inline void SetTextColor(const glm::vec4& color){m_TextColor = color;}
    inline void SetClickCallback(void(*callback)()){m_ClickCallback = callback;}
private:
    glm::vec2 m_Position = {0,0};
    glm::vec2 m_Size = {100,20};
    glm::vec4 m_Color = {0,0,0,1};
    glm::vec4 m_CurrentColor = {0,0,0,1};
    glm::vec4 m_HoverColor = {0,0,0,1};
    Texture* m_Texture = nullptr;
    SubTexture m_SubTexture{};
    Font* m_Font = nullptr;
    std::string m_Text = "";
    glm::vec4 m_TextColor = {1,1,1,1};
    void(*m_ClickCallback)() = nullptr;
};

