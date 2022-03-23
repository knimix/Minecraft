#include <iostream>
#include "GameScene.h"
#include "../World/Ray/Ray.h"

GameScene::GameScene(IO *io) : Scene(io) {
    // m_BlockHighlight = new BlockHighlight(m_Terrain->GetPlayer()->GetCamera(),m_Terrain->GetProjection());

    m_Player = new Player(io);

    m_Projection = glm::mat4(1.0f);
    m_Projection = glm::perspective(glm::radians(110.0f), (float) io->WindowWidth / (float) io->WindowHeight, 0.1f,
                                    2000.0f);

    m_Terrain = new Terrain(GetIO(), m_Projection, m_Player);


    m_BlockHighLight = new BlockHighlight(m_Projection);
    m_BlockHighLight->SetPosition({0, 10, 0});
}

GameScene::~GameScene() {
    delete m_Terrain;
}

void GameScene::Load() {
    glfwSetInputMode(reinterpret_cast<GLFWwindow *>(m_IO->Window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_HudTexture = AddTexture("../Assets/Textures/Ui/icons.png");
    Scene::Load();
}

void GameScene::Unload() {
    glfwSetInputMode(reinterpret_cast<GLFWwindow *>(m_IO->Window), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    Scene::Unload();
}

void GameScene::Update(double deltaTime) {
    Scene::Update(deltaTime);
    m_Player->Update();
    m_Terrain->Update();


    Ray ray(m_Player->GetCamera()->GetCameraPosition(), m_Player->GetCamera()->GetCameraFront());

    for (; ray.GetLength() < 5; ray.Step()) {

        glm::vec3 blockPosition = ChunkContainer::ToBlockCoord(ray.GetEndpoint());
        glm::vec3 localBlockPosition = ChunkContainer::ToLocalBlockCoord(blockPosition);

        auto chunkPosition = ChunkContainer::ToChunkCoord(blockPosition);
        Chunk *chunk = ChunkContainer::GetChunk({chunkPosition.x, chunkPosition.z});
        if(chunk == nullptr){
            break;
        }


        uint8_t block = chunk->GetBlock(localBlockPosition.x,localBlockPosition.y,localBlockPosition.z);
        if (block != 0) {
            m_BlockHighLight->SetPosition(blockPosition);
            if(m_IO->MouseClicked[GLFW_MOUSE_BUTTON_1]){
                chunk->SetBlock(localBlockPosition.x,localBlockPosition.y,localBlockPosition.z,0);
                ChunkUpdater::UpdateChunk(chunk);
            }
            if(m_IO->MouseClicked[GLFW_MOUSE_BUTTON_2]){
                ray.StepBack();
                blockPosition = ChunkContainer::ToBlockCoord(ray.GetEndpoint());
                localBlockPosition = ChunkContainer::ToLocalBlockCoord(blockPosition);


                 chunkPosition = ChunkContainer::ToChunkCoord(blockPosition);
                 chunk = ChunkContainer::GetChunk({chunkPosition.x, chunkPosition.z});
                if(chunk == nullptr){
                    break;
                }

                chunk->SetBlock(localBlockPosition.x,localBlockPosition.y,localBlockPosition.z,4);
                ChunkUpdater::UpdateChunk(chunk);
            }
            break;
        } else {
            m_BlockHighLight->SetPosition({0, -1000, 0});
        }
    }


}

void GameScene::Render() {
    Scene::Render();
    m_Player->Render();
    m_Terrain->Prepare();
    m_BlockHighLight->Render(m_Player->GetCamera()->GetViewMatrix());
    m_Terrain->Render(m_Player->GetCamera()->GetViewMatrix());
}

void GameScene::RenderUI(Renderer2D *renderer) {
    renderer->DrawQuad({m_IO->WindowWidth / 2 - 32 / 2, m_IO->WindowHeight / 2 - 32 / 2}, {32, 32}, {0, 0, 0, 0.6},
                       SubTexture(0, 0, 15, 15, m_HudTexture));
    Scene::RenderUI(renderer);
}
