#include <iostream>
#include "Application.h"
#include "../GameScenes/GameScene.h"
#include "../GameScenes/MainMenuScene.h"
#include "../GameScenes/InGame/DebugScene.h"
#include "../UI/FontManager/FontManager.h"
#include "../Resources/ResourceManager/ResourceManager.h"

static bool s_Run = true;
SceneManager* Application::SceneManager;

Application::Application() {

    srand(time(NULL));
    m_Window = new Window(1600,900,"Minecraft Clone V3");


    ResourceManager::Initialize();

    FontManager::AddFont("default",new Font("../Assets/Fonts/MinecraftRegular-Bmg3.otf",25));
    FontManager::AddFont("draw",new Font("../Assets/Fonts/MinecraftRegular-Bmg3.otf",28));

    SceneManager = new class SceneManager(m_Window->GetIO());


    SceneManager->AddScene("MainMenu", new MainMenuScene(m_Window->GetIO()));
    SceneManager->AddScene("GameView", new GameScene(m_Window->GetIO()));
    SceneManager->AddScene("DebugView", new DebugScene(m_Window->GetIO()));

    SceneManager->LoadScene("MainMenu");

}
Application::~Application() {
    FontManager::Terminate();
    ResourceManager::Shutdown();
    delete m_Window;
    delete m_Terrain;
}

void Application::Run() {
    while (!glfwWindowShouldClose(m_Window->GetBaseWindow())){
        SceneManager->BeginFrame();
        SceneManager->Clear();

        SceneManager->Update(SceneManager->GetDeltaTime());

        SceneManager->Render();
        SceneManager->RenderUI();
        ClearIO(m_Window->GetIO());
        m_Window->Update();
        SceneManager->EndFrame();

    }
}

