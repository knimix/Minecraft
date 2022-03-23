#include <iostream>
#include "Application.h"
#include "../GameScenes/GameScene.h"
#include "../GameScenes/MainMenuScene.h"
#include "../UI/FontManager/FontManager.h"

static bool s_Run = true;
SceneManager* Application::SceneManager;

Application::Application() {
    srand(time(NULL));
    m_Window = new Window(1600,900,"Minecraft Clone V3");

  /*  IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetBaseWindow(), true);
    ImGui_ImplOpenGL3_Init();*/

   FontManager::AddFont("default",new Font("../Assets/Fonts/MinecraftRegular-Bmg3.otf",25));
   // new Font("../Assets/Fonts/arial.ttf",40);
   // new Font("../Assets/Fonts/Minecraft.ttf",20);
    SceneManager = new class SceneManager(m_Window->GetIO());


    SceneManager->AddScene("MainMenu", new MainMenuScene(m_Window->GetIO()));
    SceneManager->AddScene("GameView", new GameScene(m_Window->GetIO()));

    SceneManager->LoadScene("MainMenu");

}
Application::~Application() {
    FontManager::Terminate();
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

