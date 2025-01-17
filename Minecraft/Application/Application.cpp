#include <iostream>
#include "Application.h"
#include "../GameScenes/GameScene.h"
#include "../GameScenes/MainMenuScene.h"
#include "../GameScenes/InGame/DebugScene.h"
#include "../UI/FontManager/FontManager.h"
#include "../Resources/ResourceManager/ResourceManager.h"

static bool s_Run = true;
static double s_StartTime = 0;
SceneManager* Application::m_SceneManager;
double Application::FrameTime;

Application::Application() {

    srand(time(NULL));
    m_Window = new Window(1600,900,"Minecraft Clone V3");


    ResourceManager::Initialize();

    FontManager::AddFont("default",new Font("../Assets/fonts/MinecraftRegular-Bmg3.otf",25));
    FontManager::AddFont("draw",new Font("../Assets/fonts/MinecraftRegular-Bmg3.otf",28));

    m_SceneManager = new SceneManager(m_Window->GetIO());


    m_SceneManager->AddScene("MainMenu", new MainMenuScene(m_Window->GetIO()));
    m_SceneManager->AddScene("GameView", new GameScene(m_Window->GetIO()));
    m_SceneManager->AddScene("DebugView", new DebugScene(m_Window->GetIO()));

    m_SceneManager->LoadScene("MainMenu");

}
Application::~Application() {
    FontManager::Terminate();
    ResourceManager::Shutdown();
    delete m_Window;
    delete m_Terrain;
}

void Application::Run() {
    while (!glfwWindowShouldClose(m_Window->GetBaseWindow())){
        s_StartTime = glfwGetTime();
        m_SceneManager->BeginFrame();
        m_SceneManager->Clear();

        m_SceneManager->Update(m_SceneManager->GetDeltaTime());

        m_SceneManager->Render();
        m_SceneManager->RenderUI();
        ClearIO(m_Window->GetIO());
        FrameTime = glfwGetTime() - s_StartTime;
        m_Window->Update();
        m_SceneManager->EndFrame();
    }
}

