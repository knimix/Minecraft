#pragma once
#include "../../UI/Scene/Scene.h"

class DebugScene : public Scene{
public:
    DebugScene(IO *io);

    void Load() override;
    void Unload() override;
    void Update(double deltaTime) override;
    void Render() override;
    void RenderUI(Renderer2D* renderer) override;

private:
};
