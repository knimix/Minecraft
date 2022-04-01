#pragma once
#include "../Core.h"
#include "../UI/IO/IO.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>


class Camera {

public:
    Camera(IO* io);
    void Update();
    glm::mat4 const GetViewMatrix() const;
    inline void SetCameraPosition(const glm::vec3& position){m_CameraPosition = position;}
    inline void SetCameraSpeed(float speed) {m_CameraSpeed = speed;}
    inline const glm::vec3& GetCameraPosition() const {return m_CameraPosition;}
    inline float GetYaw() const{return m_Yaw;}
    inline float GetPitch() const{return m_Pitch;}
    inline float GetCameraSpeed() const{return m_CameraSpeed;}
    inline const glm::vec3& GetCameraFront() const {return m_CameraFront;}
    inline const glm::vec3& GetCameraUp() const {return m_CameraUp;}
    inline const glm::vec3& GetCameraDirection() const {return m_CameraDirection;}
    float m_CameraSpeed = 0.1f;

private:
    IO* m_IO = nullptr;
    glm::vec3 m_CameraPosition = glm::vec3(8.f, 1.0f, 8.f);
    glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_CameraDirection;
    glm::vec3 m_Front;

    float m_Yaw   = -90.0f;
    float m_Pitch =  0.0f;
    float m_LastX = 1280 / 2;
    float m_LastY = 800 / 2;
    float m_Sensitivity = 0.08;
    bool m_FirstMouse;
};


