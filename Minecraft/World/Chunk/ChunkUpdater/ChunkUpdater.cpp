#include "ChunkUpdater.h"
#include "../ChunkManager/ChunkManager.h"


std::queue<Chunk*> ChunkUpdater::m_UpdateChunks;




ChunkUpdater::ChunkUpdater(int threadCount) {
    for (int i = 0; i < threadCount; i++) {
        auto thread = new std::thread([this] {
            while (true) {
                m_Mutex.lock();
                Chunk* chunk = nullptr;
                if (!m_UpdateChunks.empty()) {
                    chunk = m_UpdateChunks.front();
                    m_UpdateChunks.pop();
                }
                m_Mutex.unlock();

                if(chunk != nullptr){
                    if(ChunkManager::IsChunkInViewDistance(chunk)){
                        if(!chunk->m_Generated){
                            chunk->Generate();
                        }
                        chunk->Update();
                    }
                    chunk->m_Updating = false;
                }else{
                }
                std::this_thread::sleep_for(std::chrono::microseconds (1));
            }
        });
        m_Threads.emplace_back(thread);
    }
}

ChunkUpdater::~ChunkUpdater() {
   for(std::thread* thread : m_Threads){
       thread->detach();
       delete thread;
   }
}

void ChunkUpdater::UpdateChunk(Chunk *chunk) {
    chunk->m_Updating = true;
    m_UpdateChunks.emplace(chunk);
}



