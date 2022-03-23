#pragma once
#include "../World/Terrain/Terrain.h"
#include "../OpenGL/Buffer.h"
#include "../OpenGL/Shader.h"
#include "../Window/Window.h"
#include "../UI/SceneManager/SceneManager.h"

class Application {
public:
    Application();
    ~Application();
    void Run();
    static SceneManager* SceneManager;
private:
    Terrain* m_Terrain;
    Window* m_Window;
};
