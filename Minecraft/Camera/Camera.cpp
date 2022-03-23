#include "Camera.h"


Camera::Camera(IO* io) {
    m_IO = io;
}
void Camera::Update() {



    if(m_FirstMouse)
    {
        m_LastX = m_IO->MouseX;
        m_LastY = m_IO->MouseY;
        m_FirstMouse = false;
    }

    float xoffset = m_IO->MouseX - m_LastX;
    float yoffset = m_LastY - m_IO->MouseY;
    m_LastX = m_IO->MouseX;
    m_LastY = m_IO->MouseY;

    xoffset *= m_Sensitivity;
    yoffset *= m_Sensitivity;

    m_Yaw   += xoffset;
    m_Pitch += yoffset;

    if(m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if(m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(m_Front);
}

const glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
}

