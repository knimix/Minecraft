#pragma once
#include "../Scene/Scene.h"
#include <unordered_map>
#include <queue>

class SceneManager {
public:
    SceneManager(IO* io);
    ~SceneManager();

    void AddScene(const char* name, Scene* scene);
    Scene* GetScene(const char* name);
    void LoadScene(const char* name);
    void UnloadScene(const char* name);

    void Clear();
    void BeginFrame();
    void EndFrame();
    void Update(double deltaTime);
    void Render();
    void RenderUI();
    inline double GetDeltaTime() const {return m_DeltaTime;}

private:
    double m_StartTime = 0;
    double m_EndTime = 0;
    double m_DeltaTime = 0;
    std::unordered_map<std::string,Scene*> m_Scenes;
    std::unordered_map<std::string,Scene*> m_LoadedScenes;
    std::queue<Scene*> m_LoadingScenes;
    std::queue<Scene*> m_UnloadingScenes;
    Renderer2D* m_Renderer2D = nullptr;
};
