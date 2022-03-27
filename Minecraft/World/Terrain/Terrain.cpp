#include "Terrain.h"
#include <thread>
#include "imgui/imgui.h"
#include "../../Texture/Texture.h"
#include <iostream>

int Terrain::ViewDistance = 20;



Terrain::Terrain(IO* io, const glm::mat4& projection) {
    m_TerrainShader = new Shader("../Assets/Shader/TerrainShader.glsl",true);
    m_TerrainShader->SetUniformMatrix4f("projection",projection);

    m_BlockTextures = new TextureMatrix();
    auto dirtTexture = Texture::LoadTexture("../Assets/Textures/dirt.png");
    auto stoneTexture = Texture::LoadTexture("../Assets/Textures/stone.png");
    auto grassTopTexture = Texture::LoadTexture("../Assets/Textures/grass_block_top.png");
    auto grassSideTexture = Texture::LoadTexture("../Assets/Textures/grass_block_side.png");
    auto oakTexture = Texture::LoadTexture("../Assets/Textures/oak_planks.png");
    auto andesitTexture = Texture::LoadTexture("../Assets/Textures/andesite.png");
    auto dioritTexture = Texture::LoadTexture("../Assets/Textures/diorite.png");
    auto granitTexture = Texture::LoadTexture("../Assets/Textures/granite.png");

    BlockTexture stone;
    stone.Front = stoneTexture;
    stone.Back = stoneTexture;
    stone.Left = stoneTexture;
    stone.Right = stoneTexture;
    stone.Top = stoneTexture;
    stone.Bottom = stoneTexture;

    BlockTexture dirt;
    dirt.Front = dirtTexture;
    dirt.Back = dirtTexture;
    dirt.Left = dirtTexture;
    dirt.Right = dirtTexture;
    dirt.Top = dirtTexture;
    dirt.Bottom = dirtTexture;

    BlockTexture grass;
    grass.Front = grassSideTexture;
    grass.Back = grassSideTexture;
    grass.Left = grassSideTexture;
    grass.Right = grassSideTexture;
    grass.Top = grassTopTexture;
    grass.Bottom = dirtTexture;

    BlockTexture oakBlock;
    oakBlock.Front = oakTexture;
    oakBlock.Back = oakTexture;
    oakBlock.Left = oakTexture;
    oakBlock.Right = oakTexture;
    oakBlock.Top = oakTexture;
    oakBlock.Bottom = oakTexture;



    BlockTexture granitBlock;

    granitBlock.Front = granitTexture;
    granitBlock.Back = granitTexture;
    granitBlock.Left = granitTexture;
    granitBlock.Right = granitTexture;
    granitBlock.Top = granitTexture;
    granitBlock.Bottom = granitTexture;


    BlockTexture andesiteBlock;

    andesiteBlock.Front = andesitTexture;
    andesiteBlock.Back = andesitTexture;
    andesiteBlock.Left = andesitTexture;
    andesiteBlock.Right = andesitTexture;
    andesiteBlock.Top = andesitTexture;
    andesiteBlock.Bottom = andesitTexture;

    BlockTexture dioriteBlock;

    dioriteBlock.Front = dioritTexture;
    dioriteBlock.Back = dioritTexture;
    dioriteBlock.Left = dioritTexture;
    dioriteBlock.Right = dioritTexture;
    dioriteBlock.Top = dioritTexture;
    dioriteBlock.Bottom = dioritTexture;

    m_BlockTextures->AddBlockTexture(grass);
    m_BlockTextures->AddBlockTexture(dirt);
    m_BlockTextures->AddBlockTexture(stone);
    m_BlockTextures->AddBlockTexture(oakBlock);
    m_BlockTextures->AddBlockTexture(andesiteBlock);
    m_BlockTextures->AddBlockTexture(dioriteBlock);
    m_BlockTextures->AddBlockTexture(granitBlock);
    m_BlockTextures->Create(16,16,0);



}

Terrain::~Terrain() {
    delete m_TerrainShader;
   // delete m_ChunkMap;
    delete m_BlockTextures;
}
void Terrain::Prepare() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
}
void Terrain::Update(const glm::vec3& position) {

}

void Terrain::Render(const glm::mat4& view) {
    m_TerrainShader->Bind();
    m_TerrainShader->SetUniformMatrix4f("view",view);
    m_BlockTextures->Bind();
    for(auto chunk : ChunkManager::GetChunkMap()->GetChunks()){
        if(ChunkManager::IsChunkInViewDistance(chunk)){
            m_TerrainShader->SetUniformInt("chunkX",chunk->Position.x);
            m_TerrainShader->SetUniformInt("chunkZ",chunk->Position.z);
            chunk->Render();
        }
    }
}



