#include "Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>


Renderer2D::Renderer2D(IO *io) {
    m_IO = io;
    m_QuadBuffer = new Vertex[MaxVertexCount];

    m_VertexArray = new VertexArray();

    BufferLayout layout;
    layout.Push("position", GL_FLOAT, 2);
    layout.Push("textureCoords", GL_FLOAT, 2);
    layout.Push("texture", GL_FLOAT, 1);
    layout.Push("color", GL_FLOAT, 4);

    m_VertexBuffer = new VertexBuffer(0, MaxVertexCount * sizeof(Vertex), GL_DYNAMIC_DRAW);
    m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

    uint32_t indices[MaxIndexCount];
    uint32_t indexOffset = 0;
    for (int i = 0; i < MaxIndexCount; i += 6) {
        indices[i + 0] = 0 + indexOffset;
        indices[i + 1] = 1 + indexOffset;
        indices[i + 2] = 2 + indexOffset;
        indices[i + 3] = 2 + indexOffset;
        indices[i + 4] = 1 + indexOffset;
        indices[i + 5] = 3 + indexOffset;
        indexOffset += 4;
    }
    m_IndexBuffer = new IndexBuffer(indices, MaxIndexCount, GL_STATIC_DRAW);

    for (size_t i = 0; i < MaxTextures; i++) {
        m_TextureSlots[i] = 0;
    }
    m_UIShader = new Shader("../Assets/shaders/UIShader.glsl");
    m_UIShader->SetUniformInt("F_Texture0", 0);
    m_UIShader->SetUniformInt("F_Texture1", 1);
    m_UIShader->SetUniformInt("F_Texture2", 2);
    m_UIShader->SetUniformInt("F_Texture3", 3);
    m_UIShader->SetUniformInt("F_Texture4", 4);
    m_UIShader->SetUniformInt("F_Texture5", 5);
    m_UIShader->SetUniformInt("F_Texture6", 6);
    m_UIShader->SetUniformInt("F_Texture7", 7);
    m_UIShader->SetUniformInt("F_Texture8", 8);
    m_UIShader->SetUniformInt("F_Texture9", 9);
    m_UIShader->SetUniformInt("F_Texture10", 10);
    m_UIShader->SetUniformInt("F_Texture11", 11);
    m_UIShader->SetUniformInt("F_Texture12", 12);
    m_UIShader->SetUniformInt("F_Texture13", 13);
    m_UIShader->SetUniformInt("F_Texture14", 14);
    m_UIShader->SetUniformInt("F_Texture15", 15);
    m_Ortho = glm::ortho((float) 0.0f, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight, (float) 0.0f, -1.0f,
                         1.0f);
    m_UIShader->SetUniformMatrix4f("V_Ortho", m_Ortho);
}

Renderer2D::~Renderer2D() {
    delete m_VertexArray;
    delete m_VertexBuffer;
    delete m_IndexBuffer;
    delete m_UIShader;
    delete[] m_QuadBuffer;
}

void Renderer2D::BeginBatch() {
    m_QuadBufferPtr = m_QuadBuffer;
}

void Renderer2D::EndBatch() {
    GLsizeiptr size = (uint8_t *) m_QuadBufferPtr - (uint8_t *) m_QuadBuffer;
    m_VertexBuffer->Bind();
    m_VertexBuffer->SubData(m_QuadBuffer, size, 0);
}

void Renderer2D::Flush() {
    m_UIShader->Bind();
    for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
        glBindTextureUnit(i, m_TextureSlots[i]);
    }
    if (m_IO->OnWindowResize) {
        m_Ortho = glm::ortho((float) 0.0f, (float) m_IO->WindowWidth, (float) m_IO->WindowHeight, (float) 0.0f, -1.0f,
                             1.0f);
        m_UIShader->SetUniformMatrix4f("V_Ortho", m_Ortho);
        m_UIShader->SetUniformVec2("F_ScreenResolution", {(float) m_IO->WindowWidth, (float) m_IO->WindowHeight});
    }
    m_VertexArray->Bind();
    m_IndexBuffer->Bind();
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
    m_QuadCount = 0;
    m_TextureSlotIndex = 0;
    m_IndexCount = 0;

}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
    if (m_IndexCount + 6 >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    m_QuadBufferPtr->Position = position;
    m_QuadBufferPtr->TextureCoords = {0, 0};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoords = {0, 1};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y};
    m_QuadBufferPtr->TextureCoords = {1, 0};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoords = {1, 1};
    m_QuadBufferPtr->TextureIndex = -1;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;

    m_IndexCount += 6;
    m_QuadCount++;
}
void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, Texture *texture) {
    if (m_IndexCount + 6 >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    int textureIndex = -1;
    if (texture != nullptr) {
        for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
            if (m_TextureSlots[i] == texture->GetID()) {
                textureIndex = i;
                break;
            }
        }
        if (textureIndex == -1) {
            textureIndex = m_TextureSlotIndex;
            m_TextureSlots[m_TextureSlotIndex] = texture->GetID();
            m_TextureSlotIndex++;
        }

    }

    m_QuadBufferPtr->Position = position;
    m_QuadBufferPtr->TextureCoords = {0, 0};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoords = {0, 1};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y};
    m_QuadBufferPtr->TextureCoords = {1, 0};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoords = {1, 1};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;

    m_IndexCount += 6;
    m_QuadCount++;
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color,
                          const SubTexture &subTexture) {
    if (m_IndexCount + 6 >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    Texture *texture = subTexture.GetTexture();
    int textureIndex = -1;
    if (texture != nullptr) {
        for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
            if (m_TextureSlots[i] == texture->GetID()) {
                textureIndex = i;
                break;
            }
        }
        if (textureIndex == -1) {
            textureIndex = m_TextureSlotIndex;
            m_TextureSlots[m_TextureSlotIndex] = texture->GetID();
            m_TextureSlotIndex++;
        }

    }

    glm::vec4 offset = subTexture.GetTextureOffsets();
    m_QuadBufferPtr->Position = position;
    m_QuadBufferPtr->TextureCoords = {offset.x, offset.y};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoords = {offset.x, offset.w};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y};
    m_QuadBufferPtr->TextureCoords = {offset.z, offset.y};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;
    m_QuadBufferPtr->Position = {position.x + size.x, position.y + size.y};
    m_QuadBufferPtr->TextureCoords = {offset.z, offset.w};
    m_QuadBufferPtr->TextureIndex = textureIndex;
    m_QuadBufferPtr->Color = color;
    m_QuadBufferPtr++;

    m_IndexCount += 6;
    m_QuadCount++;
}


void Renderer2D::DrawString(const char *text, const Font *font, const glm::vec2 &position, const glm::vec2 &size,
                            const glm::vec4 &color, int textArrangement) {
    if (text == nullptr) {
        return;
    }
    if (font == nullptr) {
        return;
    }
    if (size.y < ((float) font->GetFontSize())) {
        return;
    }
    uint32_t textLength = strlen(text);
    if ((m_IndexCount + 6) * textLength >= MaxIndexCount || m_TextureSlotIndex > MaxTextures) {
        EndBatch();
        Flush();
        BeginBatch();
    }
    int textureIndex = -1;
    for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
        if (m_TextureSlots[i] == font->GetFontTexture()) {
            textureIndex = i;
            break;
        }
    }
    if (textureIndex == -1) {
        textureIndex = m_TextureSlotIndex;
        m_TextureSlots[m_TextureSlotIndex] = font->GetFontTexture();
        m_TextureSlotIndex++;
    }

    float cursorX = 0;
    float cursorY = 0;
    std::vector<AlignedQuad> characters;
    for (int i = 0; i < textLength; i++) {
        char character = text[i];
        if (character >= 32 && character < 128) {
            stbtt_aligned_quad q;
            stbtt_GetPackedQuad(font->GetFontData(), 1024, 1024, character - 32, &cursorX, &cursorY, &q, 1);
            AlignedQuad quad{};
            quad.qX = {q.x0, q.x1};
            quad.qY = {q.y0, q.y1};
            quad.qS = {q.s0, q.s1};
            quad.qT = {q.t0, q.t1};
            if (cursorX > size.x) {
                cursorX -= q.x1 - q.x0;
                break;
            }
            characters.emplace_back(quad);
        }
    }
    float height = (float) font->GetFontData()['H' - 32].y1 - (float) font->GetFontData()['H' - 32].y0;
    height -= height / 2;
    float x = 0;
    float y = size.y / 2 + height / 2;
    if (textArrangement == TEXT_ARRANGEMENT_LEFT) {
        x = 0;
    } else if (textArrangement == TEXT_ARRANGEMENT_RIGHT) {
        x = (size.x - cursorX);
    } else if (textArrangement == TEXT_ARRANGEMENT_CENTERED) {
        x = (size.x - cursorX) / 2;
    }
    for (AlignedQuad quad: characters) {
        m_QuadBufferPtr->Position = {quad.qX.x + position.x + x, quad.qY.y + position.y + y};
        m_QuadBufferPtr->TextureCoords = {quad.qS.x, quad.qT.y};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->Color = color;
        m_QuadBufferPtr++;
        m_QuadBufferPtr->Position = {quad.qX.x + position.x + x, quad.qY.x + position.y + y};
        m_QuadBufferPtr->TextureCoords = {quad.qS.x, quad.qT.x};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->Color = color;
        m_QuadBufferPtr++;
        m_QuadBufferPtr->Position = {quad.qX.y + position.x + x, quad.qY.y + position.y + y};
        m_QuadBufferPtr->TextureCoords = {quad.qS.y, quad.qT.y};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->Color = color;
        m_QuadBufferPtr++;
        m_QuadBufferPtr->Position = {quad.qX.y + position.x + x, quad.qY.x + position.y + y};
        m_QuadBufferPtr->TextureCoords = {quad.qS.y, quad.qT.x};
        m_QuadBufferPtr->TextureIndex = (float) textureIndex;
        m_QuadBufferPtr->Color = color;
        m_QuadBufferPtr++;
        m_IndexCount += 6;
        m_QuadCount++;
    }
}
