#pragma once
#include "../IO/IO.h"
#include "../Renderer2D/Renderer2D.h"
#include "glm/glm.hpp"

class Component {
public:
    Component() = default;
    virtual void Update(IO* io, double deltaTime){};
    virtual void Render(Renderer2D* renderer){};
};
