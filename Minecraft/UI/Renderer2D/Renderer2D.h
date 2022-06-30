#pragma once
#include "../Font/Font.h"
#include "../IO/IO.h"
#include "../../OpenGL/Buffer.h"
#include "../../OpenGL/Shader.h"
#include "../../Texture/SubTexture.h"
#include <glm/glm.hpp>
#include <array>

#define TEXT_ARRANGEMENT_CENTERED 1
#define TEXT_ARRANGEMENT_LEFT 0
#define TEXT_ARRANGEMENT_RIGHT 2

class Renderer2D {
public:
    static const size_t MaxQuadCount = 1000;
    static const size_t MaxVertexCount = MaxQuadCount * 4;
    static const size_t MaxIndexCount = MaxQuadCount * 6;
    static const size_t MaxTextures = 16;
    explicit Renderer2D(IO* io);
    ~Renderer2D();
    void BeginBatch();
    void EndBatch();
    void Flush();
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, Texture* texture);
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const SubTexture& subTexture);

    void DrawString(const char* text, const Font* font, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, int textArrangement = TEXT_ARRANGEMENT_CENTERED);
private:
    struct Vertex {
        glm::vec2 Position;
        glm::vec2 TextureCoords;
        float TextureIndex;
        glm::vec4 Color;
    };
    struct AlignedQuad {
        glm::vec2 qX;
        glm::vec2 qY;
        glm::vec2 qS;
        glm::vec2 qT;
    };
    VertexArray* m_VertexArray;
    VertexBuffer* m_VertexBuffer;
    IndexBuffer* m_IndexBuffer;
    Shader* m_UIShader;

    Vertex* m_QuadBuffer = nullptr;
    Vertex* m_QuadBufferPtr = nullptr;
    uint64_t m_QuadCount = 0;
    std::array<uint32_t, MaxTextures> m_TextureSlots{};
    uint32_t m_TextureSlotIndex = 0;
    uint32_t m_IndexCount = 0;
    IO* m_IO;
    glm::mat4 m_Ortho;
};
