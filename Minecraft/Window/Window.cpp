#include <iostream>
#include "Window.h"


Window::Window(int width, int height, const std::string &title) : m_Width(width), m_Height(height) {
    if (!glfwInit()) {
        return;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    if ((m_Window = glfwCreateWindow(width,height, title.c_str(), nullptr, NULL)) == nullptr) {
        return;
    }


    m_IO = new IO;
    m_IO->Window = m_Window;
    m_IO->WindowWidth = width;
    m_IO->WindowHeight = height;
    glfwSetWindowUserPointer(m_Window, m_IO);
    glfwSetWindowPos(m_Window, 1920 / 2 - width / 2, 1080 / 2 - height / 2);

    glfwSetWindowPosCallback(m_Window, [](GLFWwindow *nativeWindow, int x, int y) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        io->WindowX = x;
        io->WindowY = y;
        io->OnWindowMove = true;
    });
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *nativeWindow, int width, int height) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        io->WindowWidth = width;
        io->WindowHeight = height;
        io->OnWindowResize = true;
        glViewport(0,0,width,height);

    });
    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *nativeWindow, int focus) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        if (focus) {
            io->OnWindowFocus = true;
        } else {
            io->OnWindowFocusLost = true;
        }

    });
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *nativeWindow, double mouseX, double mouseY) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        io->OnMouseMove = true;
        io->MouseX = mouseX;
        io->MouseY = mouseY;

    });
    glfwSetScrollCallback(m_Window, [](GLFWwindow *nativeWindow, double xOffset, double yOffset) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        io->OnMouseScroll = true;
        io->MouseScrollX = xOffset;
        io->MouseScrollY = yOffset;
    });
    glfwSetCharCallback(m_Window, [](GLFWwindow *nativeWindow, unsigned int key) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        io->OnCharInput = true;
        io->CharInput = (char) key;

    });
    glfwSetKeyCallback(m_Window, [](GLFWwindow *nativeWindow, int key, int scanCode, int action, int mods) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        switch (action) {
            case GLFW_PRESS:
                io->Keyboard[key] = true;
                io->KeyboardClicked[key] = true;
                break;
            case GLFW_RELEASE:
                io->Keyboard[key] = false;
                io->KeyboardRepeat[key] = false;
                break;
            case GLFW_REPEAT:
                io->KeyboardRepeat[key] = true;
                break;
        }
    });
    glfwSetDropCallback(m_Window, [](GLFWwindow *nativeWindow, int count, const char *files[]) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        io->OnFilesDrop = true;
        io->DropFilesCount = count;
        io->DropFiles.clear();
        for (int i = 0; i < count; i++) {
            io->DropFiles.emplace_back(files[i]);
        }

    });
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *nativeWindow, int button, int action, int mods) {
        IO *io = reinterpret_cast<IO *>(glfwGetWindowUserPointer(nativeWindow));
        if(action == GLFW_PRESS){
            io->MouseClicked[button] = true;
        }
        io->Mouse[button] = action;
    });

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);
    gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return;
    }
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    delete m_IO;
}

void Window::Update() {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}
