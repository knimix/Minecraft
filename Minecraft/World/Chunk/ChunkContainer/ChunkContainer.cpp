#include "ChunkContainer.h"
#include "../../Terrain/Terrain.h"

Player* ChunkContainer::m_Player;
std::unordered_map<ChunkPosition,Chunk*,ChunkPositionHash> ChunkContainer::m_Chunks;
ChunkUpdater ChunkContainer::m_ChunkUpdater(4);

ChunkContainer::ChunkContainer(Player* player,Shader* terrainShader) : m_TerrainShader(terrainShader){
    m_Player = player;
}
ChunkContainer::~ChunkContainer() {

}
std::unordered_map<ChunkPosition,Chunk*,ChunkPositionHash> &ChunkContainer::GetChunks() {
    return m_Chunks;
}
Chunk *ChunkContainer::GetChunk(const glm::vec2 &position) {
    auto it = m_Chunks.find(std::make_pair((int)position.x,(int)position.y));
    if(it == m_Chunks.end()){
        return nullptr;
    }
    return it->second;
}
void ChunkContainer::Update() {
    glm::vec3 playerChunk = ToChunkCoord(m_Player->GetPosition());

        for(int x = (int)playerChunk.x - Terrain::ViewDistance; x < (int)playerChunk.x + Terrain::ViewDistance +1;x++){
            for(int z = (int)playerChunk.z - Terrain::ViewDistance; z < (int)playerChunk.z + Terrain::ViewDistance +1;z++){
                glm::vec2 currentChunk = {x, z};
                if(m_Chunks.find({x,z}) == m_Chunks.end()){
                    Chunk* chunk = new Chunk(10,x,z);
                    chunk->Create();
                    m_Chunks.insert(std::pair<std::pair<int,int>,Chunk*>({x,z}, chunk));
                    chunk->m_Updating = true;
                    ChunkUpdater::UpdateChunk(chunk);
                }

            }
        }



    std::unordered_map<std::pair<int,int>,Chunk*,ChunkPositionHash>::iterator it = m_Chunks.begin();

    while (it != m_Chunks.end()) {
        if(!IsChunkInArea(it->second,playerChunk.x - Terrain::ViewDistance  , playerChunk.x + Terrain::ViewDistance , playerChunk.z - Terrain::ViewDistance , playerChunk.z + Terrain::ViewDistance)) {
            if (!it->second->m_Updating) {
                Chunk *chunk = it->second;
                chunk->Delete();
                delete chunk;
                it = m_Chunks.erase(it);
                continue;
            }
        }
        it++;
    }

}

void ChunkContainer::Render() {
    m_TerrainShader->Bind();
    for (auto const& chunk : m_Chunks){
        m_TerrainShader->SetUniformInt("chunkX", (int)chunk.second->GetPosition().x);
        m_TerrainShader->SetUniformInt("chunkZ", (int)chunk.second->GetPosition().y);
        chunk.second->Render();
    }
}


glm::vec3 ChunkContainer::ToChunkCoord(const glm::vec3 &position) {
    return {(int)std::floor(position.x / 16.0),0,(int)std::floor(position.z / 16.0)};
}
glm::vec3 ChunkContainer::ToBlockCoord(const glm::vec3 &position) {

    return {std::floor(position.x) ,std::floor(position.y),std::floor(position.z) };
}
glm::vec3 ChunkContainer::ToLocalBlockCoord(const glm::vec3 &position) {
    auto chunkCoord = ToChunkCoord(position);
    auto blockCoord = ToBlockCoord(position);
    return {blockCoord.x - (chunkCoord.x * 16),std::floor(position.y),blockCoord.z - (chunkCoord.z * 16)};
}

void ChunkContainer::SetBlock(int x, int y, int z, uint8_t block) {
    auto chunk = GetChunk({x,z});
    if(chunk == nullptr){
        return;
    }
    glm::vec3 blockPos = ToBlockCoord({x, y, z});
    chunk->SetBlock((int)blockPos.x,(int)blockPos.y,(int)blockPos.z,block);
}
bool ChunkContainer::IsChunkInArea(Chunk *chunk, int x1, int x2, int z1, int z2) {
    glm::vec2 position = chunk->GetPosition();
    return position.x >= x1 && position.x <= x2 && position.y >= z1 && position.y <= z2;
}

bool ChunkContainer::IsChunkInPlayerRange(Chunk *chunk) {
    glm::vec3 playerChunk = ToChunkCoord(m_Player->GetPosition());
    return IsChunkInArea(chunk,playerChunk.x - Terrain::ViewDistance  , playerChunk.x + Terrain::ViewDistance , playerChunk.z - Terrain::ViewDistance , playerChunk.z + Terrain::ViewDistance);
}





