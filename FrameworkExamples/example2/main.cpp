#include <JPetManager/JPetManager.h>
#include "./JPetAnalysisModuleA.h"



using namespace std;
int main(int argc, char *argv[])
{
  JPetManager& manager = JPetManager::GetManager();
  manager.ParseCmdLine(argc, argv);
  manager.AddTask(new JPetAnalysisModuleA("Module A", "Unpack some experimental file"));
  manager.Run();

}
