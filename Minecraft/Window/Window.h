#pragma once
#include <string>
#include "../Core.h"
#include "../UI/IO/IO.h"

class Window {
public:
    Window(int width, int height,const std::string& title);
    ~Window();
    void Update();
    inline GLFWwindow* GetBaseWindow() const {return m_Window;}
    inline int GetWidth() const {return m_Width;}
    inline int GetHeight() const {return m_Height;}
    inline const std::string& GetTitle() const {return m_Title;}
    inline bool IsOpen() const {return !glfwWindowShouldClose(m_Window);}
    inline IO* GetIO(){return m_IO;};

private:
    GLFWwindow* m_Window = nullptr;
    int m_Width, m_Height;
    std::string m_Title;
    IO* m_IO;
};
