#include <iostream>
#include "SceneManager.h"
#include "../../Core.h"
#include "../FontManager/FontManager.h"

static Scene* s_CurrentScene;

SceneManager::SceneManager(IO* io) {
    m_Renderer2D = new Renderer2D(io);
}

SceneManager::~SceneManager() {
    delete m_Renderer2D;
}

void SceneManager::AddScene(const char *name, Scene *scene) {
    auto it = m_Scenes.find(name);
    if(it == m_Scenes.end()){
        scene->SceneName = name;
        m_Scenes.emplace(std::make_pair(name,scene));
    }
}

Scene *SceneManager::GetScene(const char *name) {
    auto it = m_Scenes.find(name);
    if(it != m_Scenes.end()){
        return it->second;
    }
    return nullptr;
}

void SceneManager::LoadScene(const char* name) {
    auto it = m_Scenes.find(name);
    if(it != m_Scenes.end()){
        if(!it->second->IsLoaded()){
            m_LoadingScenes.emplace(it->second);
        }
    }

}

void SceneManager::UnloadScene(const char* name) {
    auto it = m_Scenes.find(name);
    if(it != m_Scenes.end()){
        if(it->second->IsLoaded()){
            m_UnloadingScenes.emplace(it->second);
        }
    }
}


void SceneManager::Clear() {
    glClearColor(0.458, 0.729, 1,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneManager::BeginFrame() {
    m_StartTime = glfwGetTime();
}

void SceneManager::EndFrame() {
    while (!m_UnloadingScenes.empty())
    {
        Scene* scene = m_UnloadingScenes.front();
        m_LoadedScenes.erase(scene->SceneName);
        scene->Unload();
        s_CurrentScene = nullptr;
        m_UnloadingScenes.pop();
    }

    while (!m_LoadingScenes.empty())
    {
        Scene* scene = m_LoadingScenes.front();
        m_LoadedScenes.insert(std::make_pair(scene->SceneName,scene));
        scene->Load();
        s_CurrentScene = scene;
        m_LoadingScenes.pop();
    }

    m_EndTime = glfwGetTime();
    m_DeltaTime = m_EndTime - m_StartTime;
}

void SceneManager::Update(double deltaTime) {
    std::unordered_map<std::string,Scene*>::iterator it;
    for(it = m_LoadedScenes.begin(); it != m_LoadedScenes.end();it++){
        it->second->Update(deltaTime);
    }
   //if(s_CurrentScene != nullptr){
       //s_CurrentScene->Update(deltaTime);
   //}
}

void SceneManager::Render() {
   std::unordered_map<std::string,Scene*>::iterator it;
    for(it = m_LoadedScenes.begin(); it != m_LoadedScenes.end();it++){
        it->second->Render();
    }
   // if(s_CurrentScene != nullptr){
       // s_CurrentScene->Render();
    //}
}

void SceneManager::RenderUI() {
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_ALPHA_TEST);
    std::unordered_map<std::string,Scene*>::iterator it;
    m_Renderer2D->BeginBatch();

    for(it = m_LoadedScenes.begin(); it != m_LoadedScenes.end();it++){
        it->second->RenderUI(m_Renderer2D);
    }
   /* if(s_CurrentScene != nullptr){
        s_CurrentScene->RenderUI(m_Renderer2D);
    }*/
    m_Renderer2D->EndBatch();
    m_Renderer2D->Flush();
}
