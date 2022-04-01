#include "GameScene.h"
#include "../World/Ray/Ray.h"
#include "../Application/Application.h"
#include <iostream>

GameScene::GameScene(IO *io) : Scene(io) {
    // m_BlockHighlight = new BlockHighlight(m_Terrain->GetPlayer()->GetCamera(),m_Terrain->GetProjection());

    m_Player = new Player(io);

    m_Projection = glm::mat4(1.0f);
    m_Projection = glm::perspective(glm::radians(110.0f), (float) io->WindowWidth / (float) io->WindowHeight, 0.1f,
                                    2000.0f);

    ChunkManager::Initialize(123);
    ChunkManager::SetCamera(m_Player->GetCamera());

    m_Terrain = new Terrain(GetIO(), m_Projection);

    m_BlockHighLight = new BlockHighlight(m_Projection);
    m_BlockHighLight->SetPosition({0, 10, 0});
}

GameScene::~GameScene() {
    delete m_Terrain;
}

void GameScene::Load() {
    glfwSetInputMode(reinterpret_cast<GLFWwindow *>(m_IO->Window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_HudTexture = AddTexture("../Assets/textures/Ui/icons.png");
    Scene::Load();
}

void GameScene::Unload() {
    glfwSetInputMode(reinterpret_cast<GLFWwindow *>(m_IO->Window), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    Scene::Unload();
}
int calcOrder( const glm::vec3 & dir )
{
    int signs;

    const int   sx = dir.x<0.0f;
    const int   sy = dir.y<0.0f;
    const int   sz = dir.z<0.0f;
    const float ax = fabsf( dir.x );
    const float ay = fabsf( dir.y );
    const float az = fabsf( dir.z );

    if( ax>ay && ax>az )
    {
        if( ay>az ) signs = 0 + ((sx<<2)|(sy<<1)|sz);
        else        signs = 8 + ((sx<<2)|(sz<<1)|sy);
    }
    else if( ay>az )
    {
        if( ax>az ) signs = 16 + ((sy<<2)|(sx<<1)|sz);
        else        signs = 24 + ((sy<<2)|(sz<<1)|sx);
    }
    else
    {
        if( ax>ay ) signs = 32 + ((sz<<2)|(sx<<1)|sy);
        else        signs = 40 + ((sz<<2)|(sy<<1)|sx);
    }

    return signs;
}
void GameScene::Update(double deltaTime) {
    Scene::Update(deltaTime);


    m_Player->Update();
    m_Terrain->Update(m_Player->GetPosition());

    ChunkManager::Update(deltaTime);


    if(m_IO->Mouse[GLFW_MOUSE_BUTTON_3]){
        auto front = m_Player->GetCamera()->GetCameraFront();


    /*    if(front.z >= 0 && front.z <= 1){
          //  std::cout << "front!\n";
        }
        if(front.z <= 0 && front.z >= -1){
            //std::cout << "back!\n";
        }

        if(front.x >= 0 && front.x <= 1){
            std::cout << "left!\n";
        }
        if(front.x <= 0 && front.x >= -1){
            std::cout << "right!\n";
        }*/


        std::cout << "Direction X: " << front.x << std::endl;
    }


    if(m_IO->KeyboardClicked[GLFW_KEY_F3]){
        m_ToggleDebug = !m_ToggleDebug;
        if(m_ToggleDebug){
            Application::SceneManager->LoadScene("DebugView");
        }else{
            Application::SceneManager->UnloadScene("DebugView");
        }
    }

    Ray ray(m_Player->GetCamera()->GetCameraPosition(), m_Player->GetCamera()->GetCameraFront());

    for (; ray.GetLength() < 5; ray.Step()) {

        auto blockPosition = Coordinate::ToBlockPosition(ray.GetEndpoint());
        auto localBlockPosition = Coordinate::ToLocalBlockPosition(blockPosition);

        auto chunkPosition = Coordinate::ToChunkPosition(blockPosition);
        Chunk *chunk = ChunkManager::GetChunkMap()->GetChunk(chunkPosition);
        if(chunk == nullptr){
            break;
        }

        if(blockPosition.y < 0 || blockPosition.y > 255){
            continue;
        }

        uint8_t block = chunk->GetBlock(localBlockPosition.x,localBlockPosition.y,localBlockPosition.z);
        if (block != 0) {
            m_BlockHighLight->SetPosition({blockPosition.x, blockPosition.y, blockPosition.z});
            if(m_IO->MouseClicked[GLFW_MOUSE_BUTTON_1]){
                ChunkManager::SetBlock(blockPosition.x, blockPosition.y, blockPosition.z,0);


            }for(int x = blockPosition.x - 10; x <= blockPosition.x + 10;x++){

                //ChunkUpdater::UpdateChunk(chunk);
            }
            if(m_IO->MouseClicked[GLFW_MOUSE_BUTTON_2]){
                ray.StepBack();
                blockPosition = Coordinate::ToBlockPosition(ray.GetEndpoint());
                localBlockPosition = Coordinate::ToLocalBlockPosition(blockPosition);


                chunkPosition = Coordinate::ToChunkPosition(blockPosition);
                chunk = ChunkManager::GetChunkMap()->GetChunk({chunkPosition.x, chunkPosition.z});
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
