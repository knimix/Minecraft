#include <iostream>
#include "Minecraft/Application/Application.h"



int main() {
   auto* application = new Application();

   application->Run();

   delete application;

}
