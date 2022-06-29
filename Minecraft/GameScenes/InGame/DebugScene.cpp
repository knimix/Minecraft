#include <iostream>
#include "DebugScene.h"
#include "../../World/Chunk/ChunkManager/ChunkManager.h"
#include "../../Application/Application.h"

DebugScene::DebugScene(IO *io) : Scene(io) {

}

void DebugScene::Load() {
    Scene::Load();
    std::cout << "Loaded!\n";
}

void DebugScene::Unload() {
    Scene::Unload();
}

void DebugScene::Update(double deltaTime) {
    Scene::Update(deltaTime);
}

void DebugScene::Render() {
    Scene::Render();
}

void DebugScene::RenderUI(Renderer2D *renderer) {
    Scene::RenderUI(renderer);
    auto camera = ChunkManager::GetCamera();
    auto currentBlockPos = Coordinate::ToBlockPosition(camera->GetCameraPosition());
    auto currentLocalBlockPos = Coordinate::ToLocalBlockPosition(currentBlockPos);
    auto chunkPos = Coordinate::ToChunkPosition(currentBlockPos);

    std::string chunkPosString = "Current Chunk X: " + std::to_string(chunkPos.x) + " Z: " + std::to_string(chunkPos.z);
    std::string blockPosString = "Current Block X: " + std::to_string(currentBlockPos.x) + " Y: " + std::to_string(currentBlockPos.y) + " Z: " + std::to_string(currentBlockPos.z);
    std::string localPosString = "Current Local Block X: " + std::to_string(currentLocalBlockPos.x) + " Y: " + std::to_string(currentLocalBlockPos.y) + " Z: " + std::to_string(currentLocalBlockPos.z);
    std::string chunksQueueString = "Chunks in Update Queue: " + std::to_string(ChunkManager::GetChunkUpdater()->GetChunkQueue().size());
    std::string chunksGeneratorQueueString = "Chunks in Generator Queue: " + std::to_string(ChunkManager::GetChunkGenerator()->GetChunkQueue().size());
    std::string ChunksViewString = "Loaded Chunks: " + std::to_string(ChunkManager::GetChunkMap()->GetChunkMap().size());
    std::string FrameTime = "Frame Time: " + std::to_string(std::round(Application::FrameTime * 1000)) + " ms";
    if(glfwGetTime() - m_LastUpdate >= 0.6){
        m_LastUpdate = glfwGetTime();
        m_FPS = "FPS: " + std::to_string((int)std::round(1000.0 / (Application::FrameTime * 1000)));
    }
    renderer->DrawString(chunkPosString.c_str(), FontManager::GetFont("draw"),{12,0},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_LEFT);
    renderer->DrawString(blockPosString.c_str(), FontManager::GetFont("draw"),{12,30},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_LEFT);
    renderer->DrawString(localPosString.c_str(), FontManager::GetFont("draw"),{12,60},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_LEFT);
    renderer->DrawString(chunksQueueString.c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,0},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);
    renderer->DrawString(chunksGeneratorQueueString.c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,30},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);
    renderer->DrawString(ChunksViewString.c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,60},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);
    renderer->DrawString(FrameTime.c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,150},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);
    renderer->DrawString(m_FPS.c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,180},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);


    int64_t size = 0;
    int64_t faces = 0;
    for(auto chunk : ChunkManager::GetChunkMap()->GetChunks()){
        size+= chunk->GetBlockBuffer().size() * 4;
        faces+= chunk->GetBlockBuffer().size() / 3;
    }
    double kb = size / 1024.0;
    double mb = kb / 1024.0;
    renderer->DrawString(std::string(std::string("Mesh Data: ") + std::to_string( mb )+ " mb").c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,90},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);
    renderer->DrawString(std::string(std::string("Faces: ") + std::to_string( faces )).c_str(), FontManager::GetFont("draw"),{m_IO->WindowWidth - 612,120},{600,30},{1,1,1,1},TEXT_ARRANGEMENT_RIGHT);



}
