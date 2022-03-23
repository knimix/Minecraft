#pragma once
#include "glm/glm.hpp"

class Ray {
public:
    Ray(const glm::vec3 startPosition, const glm::vec3& direction);
    void Step();
    void StepBack();
    inline float GetLength(){return glm::length(m_End - m_Start);}
    inline glm::vec3 GetEndpoint(){return m_End;}
    inline glm::vec3 GetLastPoint(){return m_Previous;}


private:
    glm::vec3 m_Start;
    glm::vec3 m_Previous;
    glm::vec3 m_End;
    glm::vec3 m_Direction;
};
