cmake_minimum_required(VERSION 3.20)
project(Minecraft)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES Minecraft/*.cpp Minecraft/*.h Minecraft/*.c)
if(WIN32)
    include_directories(dependencies/GLFW/include)
    include_directories(dependencies/OpenGL/include)
    include_directories(dependencies/GLM/include)
    include_directories(dependencies/STB/include)
    include_directories(dependencies/Json/include)
endif()

include_directories(dependencies/FastNoise/src)
include_directories(dependencies/Glad/include)

add_executable(Minecraft main.cpp ${SOURCE_FILES} ${IMGUI_FILES} dependencies/FastNoise/src/FastNoise/FastNoise.cpp dependencies/Glad/src/glad.c)

if(WIN32)
target_link_libraries(Minecraft ${CMAKE_CURRENT_LIST_DIR}/dependencies/OpenGL/bin/OpenGL.a ${CMAKE_CURRENT_LIST_DIR}/dependencies/GLFW/bin/GLFW.a)
else()
    target_link_libraries(Minecraft glfw)
endif()