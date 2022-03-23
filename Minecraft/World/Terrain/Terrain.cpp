#include "Terrain.h"
#include <thread>
#include "imgui/imgui.h"
#include "../../Texture/Texture.h"

std::unordered_map<uint8_t,BlockTexture> Terrain::BlockTextures;
int Terrain::ViewDistance = 20;



Terrain::Terrain(IO* io, const glm::mat4& projection,Player* player) {
    m_Player = player;

    m_TerrainShader = new Shader("../Assets/Shader/TerrainShader.glsl",true);
    m_TerrainShader->Bind();
    m_TerrainShader->SetUniformMatrix4f("projection",projection);
    m_ChunkContainer = new ChunkContainer(m_Player,m_TerrainShader);

    m_TextureMatrix = new TextureMatrix();

    auto dirtTexture = Texture::LoadTexture("../Assets/Textures/dirt.png");
    auto stoneTexture = Texture::LoadTexture("../Assets/Textures/stone.png");
    auto grassTopTexture = Texture::LoadTexture("../Assets/Textures/grass_block_top.png");
    auto grassSideTexture = Texture::LoadTexture("../Assets/Textures/grass_block_side.png");
    auto oakTexture = Texture::LoadTexture("../Assets/Textures/oak_planks.png");
    auto andesitTexture = Texture::LoadTexture("../Assets/Textures/andesite.png");
    auto dioritTexture = Texture::LoadTexture("../Assets/Textures/diorite.png");
    auto granitTexture = Texture::LoadTexture("../Assets/Textures/granite.png");
  //  auto tomTexture = Texture::LoadTexture("../Assets/Textures/tom.jpg");


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

    m_TextureMatrix->AddBlockTexture(grass);
    m_TextureMatrix->AddBlockTexture(dirt);
    m_TextureMatrix->AddBlockTexture(stone);
    m_TextureMatrix->AddBlockTexture(oakBlock);
    m_TextureMatrix->AddBlockTexture(andesiteBlock);
    m_TextureMatrix->AddBlockTexture(dioriteBlock);
    m_TextureMatrix->AddBlockTexture(granitBlock);

    m_TextureMatrix->Create(16,16,0);
}

Terrain::~Terrain() {
    delete m_TerrainShader;
    delete m_ChunkContainer;
    delete m_TextureMatrix;
}
void Terrain::Prepare() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
}
void Terrain::Update() {
    m_ChunkContainer->Update();
}

void Terrain::Render(const glm::mat4& view) {
    m_TerrainShader->Bind();
    m_TerrainShader->SetUniformMatrix4f("view",view);
    m_TextureMatrix->Bind();
    m_ChunkContainer->Render();
}



