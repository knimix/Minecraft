#include "ChunkGenerator.h"
#include "../ChunkManager/ChunkManager.h"

std::queue<Chunk*> ChunkGenerator::m_GenerateChunks;

ChunkGenerator::ChunkGenerator(int threadCount) {
    for (int i = 0; i < threadCount; i++) {
        std::thread *thread;
        thread = new std::thread([this] {
            while (true) {
                m_Mutex.lock();
                Chunk *chunk = nullptr;
                if (!m_GenerateChunks.empty()) {
                    chunk = m_GenerateChunks.front();
                    m_GenerateChunks.pop();
                }
                m_Mutex.unlock();

                if (chunk != nullptr) {
                    if (ChunkManager::IsChunkInPreCreateDistance(chunk)) {
                        if (!chunk->Generated) {
                            chunk->Generate();
                        }
                    }
                    chunk->Generating = false;
                } else {
                    std::this_thread::sleep_for(std::chrono::microseconds (1));                }
            }
        });
        m_Threads.emplace_back(thread);
    }
}

ChunkGenerator::~ChunkGenerator() {
    for(std::thread* thread : m_Threads){
        thread->detach();
        delete thread;
    }
}

void ChunkGenerator::GenerateChunk(Chunk *chunk) {
    chunk->Generating = true;
    m_GenerateChunks.emplace(chunk);
}
