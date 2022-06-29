#include "BlockHighlight.h"

BlockHighlight::BlockHighlight(const glm::mat4& projection) {
    m_BlockHighlightShader = new Shader("../Assets/Shader/BlockHighlight.glsl");
    m_BlockHighlightShader->SetUniformMatrix4f("projection",projection);
    m_VertexArray = new VertexArray();

    float vertices[8 * 3]{
        0,0,0,
        1,0,0,
        1,1,0,
        0,1,0,

        0,0,1,
        1,0,1,
        1,1,1,
        0,1,1,
    };
    uint32_t indices[]{
        0,1,
        1,2,
        2,3,
        3,0,
        4,5,
        5,6,
        6,7,
        7,4,
        0,4,
        1,5,
        2,6,
        3,7

    };
    m_VertexBuffer = new VertexBuffer(vertices,sizeof(vertices),GL_STATIC_DRAW);

    BufferLayout layout;
    layout.Push("position",GL_FLOAT,3);
    m_VertexArray->AddBuffer(*m_VertexBuffer,layout);
    m_IndexBuffer = new IndexBuffer(indices,sizeof(indices),GL_STATIC_DRAW);

}

BlockHighlight::~BlockHighlight() {

}

void BlockHighlight::Render(const glm::mat4& view) {
    m_BlockHighlightShader->Bind();
    m_BlockHighlightShader->SetUniformMatrix4f("view",view);
    m_BlockHighlightShader->SetUniformMatrix4f("model",glm::scale(m_Model,glm::vec3(1.001,1.001,1.001)));
    m_VertexArray->Bind();
    glLineWidth(3);

    glDrawElements(GL_LINES,12*2,GL_UNSIGNED_INT, nullptr);
}
