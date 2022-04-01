#include <mutex>
#include "ChunkMap.h"

void ChunkMap::AddChunk(Chunk *chunk,const ChunkPosition& chunkPosition) {
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Chunks.insert(std::make_pair(chunkPosition, chunk));
}

void ChunkMap::RemoveChunk(const ChunkPosition& chunkPosition) {
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Chunks.erase(chunkPosition);
}

Chunk *ChunkMap::GetChunk(const ChunkPosition& chunkPosition, bool lock) {
    std::unique_lock<std::mutex> lock_(m_Mutex);
    auto it = m_Chunks.find(chunkPosition);
    if (it == m_Chunks.end()) {
        return nullptr;
    }
    if(lock){
        it->second->Accessed = true;
    }
    return it->second;
}

bool ChunkMap::ChunkExist(const ChunkPosition &chunkPosition) {
    return GetChunk(chunkPosition) != nullptr;
}

std::vector<Chunk *> ChunkMap::GetChunks() {
    std::unique_lock<std::mutex> lock(m_Mutex);
    std::vector<Chunk*> chunks;
    for(auto const& chunk : m_Chunks){
        chunks.emplace_back(chunk.second);
    }
    return chunks;
}

void ChunkMap::UnlockChunk(Chunk* chunk) {
    if(chunk != nullptr){
        chunk->Accessed = false;
    }
}



