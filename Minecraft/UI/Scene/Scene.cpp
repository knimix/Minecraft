#include "Scene.h"

void Scene::Load() {
    m_Loaded = true;
}

void Scene::Unload() {
    for(Component* component : m_Components){
        delete component;
    }
    for(Texture* texture : m_Textures){
        delete texture;
    }
    m_Components.clear();
    m_Textures.clear();
    m_Loaded = false;
}

void Scene::Update(double deltaTime) {
    for(Component* component : m_Components){
        component->Update(m_IO,deltaTime);
    }
}

void Scene::Render() {

}

void Scene::RenderUI(Renderer2D* renderer) {
    for(Component* component : m_Components){
        component->Render(renderer);
    }
}

template<>
Button* Scene::AddComponent<Button>(){
    auto button = new Button();
    m_Components.emplace_back(button);
    return button;
}

Texture *Scene::AddTexture(const char *path) {
    auto texture = new Texture();
    texture->Load(path);
    m_Textures.emplace_back(texture);
    return texture;
}


