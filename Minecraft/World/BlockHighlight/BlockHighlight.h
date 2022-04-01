#pragma once
#include "../../OpenGL/Buffer.h"
#include "../../OpenGL/Shader.h"
#include "../../Camera/Camera.h"
class BlockHighlight {
public:
    BlockHighlight(const glm::mat4& projection);
    ~BlockHighlight();
    void Render(const glm::mat4& view);
    inline void SetPosition(const glm::vec3& position){m_Position = position; m_Model = glm::translate(glm::mat4(1.0),position);}

private:
    glm::vec3 m_Position = {0,0,0};
    glm::mat4 m_Model;
    Shader* m_BlockHighlightShader = nullptr;
    VertexArray* m_VertexArray = nullptr;
    VertexBuffer* m_VertexBuffer = nullptr;
    IndexBuffer* m_IndexBuffer = nullptr;
};
