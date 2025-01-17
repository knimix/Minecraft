cmake_minimum_required(VERSION 3.20)
project(Minecraft)

set(CMAKE_CXX_STANDARD 23)

find_package(glfw3)
find_package(glad)
find_package(glm)
find_package(stb)
find_package(nlohmann_json)


file(GLOB_RECURSE SOURCE_FILES Minecraft/*.cpp Minecraft/*.h Minecraft/*.c)

add_executable(Minecraft main.cpp ${SOURCE_FILES})

target_link_libraries(Minecraft glad::glad glm::glm stb::stb nlohmann_json::nlohmann_json glfw)
