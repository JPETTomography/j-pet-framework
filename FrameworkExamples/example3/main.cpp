#include <iostream>
#include <JPetManager/JPetManager.h>
#include "./JPetAnalysisModuleContainers.h"


int main(int argc, char *argv[])
{
  JPetManager& manager = JPetManager::GetManager();
  manager.ParseCmdLine(argc, argv);
  manager.AddTask(new JPetAnalysisModuleContainers("Module Containers", "Test Containers"));
  manager.Run();
  
  return 0;
}
