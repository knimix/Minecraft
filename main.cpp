#include <iostream>
#include "Minecraft/Application/Application.h"
#include "Minecraft/World/Chunk/ChunkContainer/ChunkContainer.h"



int main() {
   auto* application = new Application();

   application->Run();

   delete application;

}