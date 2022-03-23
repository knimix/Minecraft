#pragma once
#include "../IO/IO.h"
#include "../Renderer2D/Renderer2D.h"
#include "../Components/Button/Button.h"
#include "../FontManager/FontManager.h"

class Scene {
public:
    explicit Scene(IO* io) : m_IO(io){};
    virtual void Load();
    virtual void Unload();
    virtual void Update(double deltaTime);
    virtual void Render();
    virtual void RenderUI(Renderer2D* renderer);

    template<class T>
    T* AddComponent();
    Texture* AddTexture(const char* path);

    inline bool IsLoaded() const{return m_Loaded;}
    inline IO* GetIO(){return m_IO;}
    std::string SceneName;
private:
    std::vector<Component*> m_Components;
    std::vector<Texture*> m_Textures;
    bool m_Loaded = false;
protected:
    IO* m_IO = nullptr;
};
