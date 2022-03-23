#pragma once

#include <vector>
#include <string>
#include <string.h>

struct IO {
    bool OnWindowMove = false;
    int WindowX = 100, WindowY = 100;
    bool OnWindowResize = false;
    int WindowWidth = 1600, WindowHeight = 900;
    bool OnWindowFocus = false;
    bool OnWindowFocusLost = false;
    bool OnMouseMove = false;
    double MouseX = 0, MouseY = 0;
    double ScreenMouseX = 0, ScreenMouseY = 0;
    bool OnMouseScroll = false;
    double MouseScrollX = 0;
    double MouseScrollY = 0;
    bool OnCharInput = false;
    char CharInput = '\0';
    bool OnFilesDrop = false;
    int DropFilesCount = 0;
    bool OnWindowTitleChange = false;
    const char *WindowTitle = nullptr;
    std::vector<std::string> DropFiles;
    bool Keyboard[348] = {false};
    bool KeyboardRepeat[348] = {false};
    bool KeyboardClicked[348] = {false};
    bool Mouse[8] = {false};
    bool MouseClicked[8] = {false};
    bool Joystick[16] = {false};
    void* Window = nullptr;
    bool Exit = false;
};

inline void ClearIO(IO *io) {
    io->OnWindowMove = false;
    io->OnWindowResize = false;
    io->OnMouseMove = false;
    io->OnCharInput = false;
    io->OnFilesDrop = false;
    io->OnWindowFocus = false;
    io->OnWindowFocusLost = false;
    io->OnMouseScroll = false;
    io->OnWindowTitleChange = false;
    memset(io->MouseClicked, false, 8);
    memset(io->KeyboardClicked, false, 348);
}
