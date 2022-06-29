#include "Terrain.h"
#include "../../Texture/Texture.h"
#include "../../Resources/TextureManager/TextureManager.h"

Terrain::Terrain(IO *io, const glm::mat4 &projection) {
    m_TerrainShader = new Shader("../Assets/Shader/TerrainShader.glsl", true);
    m_TerrainShader->SetUniformMatrix4f("projection", projection);

}

Terrain::~Terrain() {
    delete m_TerrainShader;
}

void Terrain::Prepare() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
   glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
    glEnable(GL_ALPHA_TEST);
}

void Terrain::Update(const glm::vec3 &position) {

}

void Terrain::Render(const glm::mat4 &view) {
    m_TerrainShader->Bind();
    m_TerrainShader->SetUniformMatrix4f("view", view);
    TextureManager::GetFaceTextureMatrix()->Bind();
    for (auto chunk: ChunkManager::GetChunkMap()->GetChunks()) {
        if (ChunkManager::IsChunkInViewDistance(chunk)) {
            m_TerrainShader->SetUniformInt("chunkX", chunk->Position.x);
            m_TerrainShader->SetUniformInt("chunkZ", chunk->Position.z);
            chunk->Render();
        }
    }

}



