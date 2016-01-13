#include <JPetManager/JPetManager.h>

#include <TString.h>

using namespace std;
int main(int argc, char* argv[])
{
  JPetManager& manager = JPetManager::getManager();
  manager.parseCmdLine(argc, argv);
  manager.run();
}
