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

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(Minecraft main.cpp ${SOURCE_FILES} ${IMGUI_FILES} dependencies/FastNoise/src/FastNoise/FastNoise.cpp Minecraft/World/Chunk/BlockHighlight/BlockHighlight.cpp Minecraft/World/Chunk/BlockHighlight/BlockHighlight.h Minecraft/World/Chunk/ChunkMap/ChunkMap.cpp Minecraft/World/Chunk/ChunkMap/ChunkMap.h Minecraft/World/Chunk/ChunkManager/ChunkManager.cpp Minecraft/World/Chunk/ChunkManager/ChunkManager.h Minecraft/World/Chunk/Coordinate.h Minecraft/World/Chunk/Coordinate.cpp)

target_link_libraries(Minecraft ${CMAKE_CURRENT_LIST_DIR}/dependencies/OpenGL/bin/OpenGL.a ${CMAKE_CURRENT_LIST_DIR}/dependencies/GLFW/bin/GLFW.a )
