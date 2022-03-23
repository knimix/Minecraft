#pragma once
#include "../UI/Scene/Scene.h"
#include "../World/Terrain/Terrain.h"
#include "../World/Chunk/BlockHighlight/BlockHighlight.h"

class GameScene : public Scene{
public:
    GameScene(IO *io);
    ~GameScene();
    void Load() override;
    void Unload() override;
    void Update(double deltaTime) override;
    void Render() override;
    void RenderUI(Renderer2D* renderer) override;

private:
    glm::mat4 m_Projection;
    Texture* m_HudTexture = nullptr;
    Terrain* m_Terrain = nullptr;
    Player* m_Player = nullptr;
    BlockHighlight* m_BlockHighLight = nullptr;
};
