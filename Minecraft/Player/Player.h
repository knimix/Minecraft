#pragma once
#include "../Camera/Camera.h"

class Player {
public:
    Player(IO* io);
    void Update();
    void Render();
    inline Camera* GetCamera()const {return m_Camera;}
    inline const glm::vec3& GetPosition() const {return m_Position;}

private:
    bool m_Filled = false;
    bool m_Cursor = false;
    IO* m_IO = nullptr;
    glm::vec3 m_Position = {8.f,0,8.f};
    Camera* m_Camera = nullptr;
};
