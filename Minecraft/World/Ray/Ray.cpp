#include "Ray.h"



Ray::Ray(const glm::vec3 startPosition, const glm::vec3 &direction) {
    m_Start = startPosition;
    m_Previous = startPosition;
    m_End = startPosition;
    m_Direction = direction;
}

void Ray::Step() {
    m_Previous = m_End;
    m_End += (m_Direction * glm::vec3(0.1f));
}

void Ray::StepBack() {
    m_Previous = m_End;
    m_End -= m_Direction ;
}
