#include "MainMenuScene.h"
#include "../Application/Application.h"

MainMenuScene::MainMenuScene(IO *io) : Scene(io) {

}

void MainMenuScene::Load() {
    Scene::Load();

    auto buttonTexture = AddTexture("../Assets/Textures/Ui/widgets.png");
    m_Background = AddTexture("../Assets/Textures/Ui/background.png");
    m_Font = FontManager::GetFont("default");


    m_SinglePlayerButton = AddComponent<Button>();
    m_SinglePlayerButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2 - 50});
    m_SinglePlayerButton->SetSize({400,40});
    m_SinglePlayerButton->SetSubTexture(SubTexture(0,66,200,86,buttonTexture));
    m_SinglePlayerButton->SetFont(m_Font);
    m_SinglePlayerButton->SetHover({0.1,0.1,0.25,1.0});
    m_SinglePlayerButton->SetText("Singleplayer");
    m_SinglePlayerButton->SetClickCallback([](){
        Application::SceneManager->UnloadScene("MainMenu");
        Application::SceneManager->LoadScene("GameView");
    });

    m_MultiplayerButton = AddComponent<Button>();
    m_MultiplayerButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2});
    m_MultiplayerButton->SetSize({400,40});
    m_MultiplayerButton->SetSubTexture(SubTexture(0,66,200,86,buttonTexture));
    m_MultiplayerButton->SetFont(m_Font);
    m_MultiplayerButton->SetHover({0.1,0.1,0.25,1.0});
    m_MultiplayerButton->SetText("Multiplayer");

    m_RealmsButton = AddComponent<Button>();
    m_RealmsButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2 + 50});
    m_RealmsButton->SetSize({400,40});
    m_RealmsButton->SetSubTexture(SubTexture(0,66,200,86,buttonTexture));
    m_RealmsButton->SetFont(m_Font);
    m_RealmsButton->SetHover({0.1,0.1,0.25,1.0});
    m_RealmsButton->SetText("Minecraft Realms");

    m_OptionsButton = AddComponent<Button>();
    m_OptionsButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2 + 125});
    m_OptionsButton->SetSize({195,40});
    m_OptionsButton->SetSubTexture(SubTexture(0,66,200,86,buttonTexture));
    m_OptionsButton->SetFont(m_Font);
    m_OptionsButton->SetHover({0.1,0.1,0.25,1.0});
    m_OptionsButton->SetText("Options...");

    m_QuitGameButton = AddComponent<Button>();
    m_QuitGameButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2 + 205,m_IO->WindowHeight / 2 - 40 / 2 + 125});
    m_QuitGameButton->SetSize({195,40});
    m_QuitGameButton->SetSubTexture(SubTexture(0,66,200,86,buttonTexture));
    m_QuitGameButton->SetFont(m_Font);
    m_QuitGameButton->SetHover({0.1,0.1,0.25,1.0});
    m_QuitGameButton->SetText("Quit Game");
    m_QuitGameButton->SetClickCallback([](){
       exit(0);
    });

    m_LanguageButton = AddComponent<Button>();
    m_LanguageButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2 - 50,m_IO->WindowHeight / 2 - 40 / 2 + 125});
    m_LanguageButton->SetSize({40,40});
    m_LanguageButton->SetSubTexture(SubTexture(0,106,20,126,buttonTexture));
    m_LanguageButton->SetHover({0.1,0.1,0.25,1.0});
}

void MainMenuScene::Unload() {
    Scene::Unload();
}

void MainMenuScene::Update(double deltaTime) {
    Scene::Update(deltaTime);
    if(m_IO->OnWindowResize){
        m_SinglePlayerButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2 - 50});
        m_MultiplayerButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2});
        m_RealmsButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2 + 50});
        m_OptionsButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2,m_IO->WindowHeight / 2 - 40 / 2 + 125});
        m_QuitGameButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2 + 205,m_IO->WindowHeight / 2 - 40 / 2 + 125});
        m_LanguageButton->SetPosition({m_IO->WindowWidth / 2 - 400 / 2 - 50,m_IO->WindowHeight / 2 - 40 / 2 + 125});
    }
}

void MainMenuScene::Render() {
    Scene::Render();
}

void MainMenuScene::RenderUI(Renderer2D *renderer) {
    renderer->DrawQuad({0,0},{m_IO->WindowWidth,m_IO->WindowHeight},{0,0,0,1},m_Background);
    renderer->DrawString("Minecraft Clone V3",m_Font,{5,m_IO->WindowHeight - 35},{200,40},{1,1,1,1});
    renderer->DrawString("Copyright Konrad. Do not distribute!",m_Font,{m_IO->WindowWidth - 400,m_IO->WindowHeight - 35},{400,40},{1,1,1,1});
    Scene::RenderUI(renderer);
}
