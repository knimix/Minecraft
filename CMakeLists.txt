cmake_minimum_required(VERSION 3.20)
project(Minecraft)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES Minecraft/*.cpp Minecraft/*.h Minecraft/*.c)
file(GLOB_RECURSE IMGUI_FILES dependencies/ImGui/src/*.h dependencies/ImGui/src/*.cpp dependencies/ImGui/src/*.c)

include_directories(dependencies/OpenGL/include)
include_directories(dependencies/GLFW/include)
include_directories(dependencies/GLM/include)
include_directories(dependencies/ImGui/src)
include_directories(dependencies/STB/include)
include_directories(dependencies/FastNoise/src)
include_directories(dependencies/Fusion/Include)
include_directories(dependencies/Json/include)



add_executable(Minecraft main.cpp ${SOURCE_FILES} ${IMGUI_FILES} dependencies/FastNoise/src/FastNoise/FastNoise.cpp Minecraft/Resources/JsonLoader.cpp Minecraft/Resources/JsonLoader.h Minecraft/Resources/BlockManager/BlockManager.cpp Minecraft/Resources/BlockManager/BlockManager.h Minecraft/Resources/TextureManager/TextureManager.cpp Minecraft/Resources/TextureManager/TextureManager.h)

target_link_libraries(Minecraft ${CMAKE_CURRENT_LIST_DIR}/dependencies/OpenGL/bin/OpenGL.a ${CMAKE_CURRENT_LIST_DIR}/dependencies/GLFW/bin/GLFW.a )
