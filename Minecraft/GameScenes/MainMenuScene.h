#pragma once
#include "../UI/Scene/Scene.h"

class MainMenuScene : public Scene{
public:
    MainMenuScene(IO *io);

    void Load() override;
    void Unload() override;
    void Update(double deltaTime) override;
    void Render() override;
    void RenderUI(Renderer2D* renderer) override;

private:
    Button* m_SinglePlayerButton = nullptr;
    Button* m_MultiplayerButton = nullptr;
    Button* m_RealmsButton = nullptr;
    Button* m_OptionsButton = nullptr;
    Button* m_QuitGameButton = nullptr;
    Button* m_LanguageButton = nullptr;
    Texture* m_Background = nullptr;
    Font* m_Font = nullptr;
};
