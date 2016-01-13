#include "JPetManager/JPetManager.h"
#include "ModuleA.h"
#include "ModuleB.h"
#include "ModuleC1.h"
#include "ModuleC2.h"
#include "ModuleC3.h"
#include "ModuleD.h"
#include "ModuleE.h"

#include <TString.h>

using namespace std;
int main(int argc, char* argv[]) {
  JPetManager& manager = JPetManager::GetManager();
  manager.ParseCmdLine(argc, argv);

  // Here create all analysis modules to be used:
    auto generatorChain = new TaskGeneratorChain();
    generatorChain->push_back([](){
        return new ModuleA("Module A: Unp to TSlot Raw",
                           "Process unpacked HLD file into a tree of JPetTimeWindow objects",
                           "hld.root", "tslot.raw.root");
    });
    generatorChain->push_back([](){
        return new ModuleB("Module B: TSlot Raw to TSlot Cal",
                           "Calibrate Raw TSlot and write to TSlot Cal",
                           "tslot.raw.root", "tslot.cal.root");
    });
    generatorChain->push_back([](){
        return new ModuleC1("Module C1: TSlot Cal to Raw Signal",
                           "Build Raw Signals from Calibrated TSlots",
                           "tslot.cal.root", "raw.sig.root");
    });
    generatorChain->push_back([](){
        return new ModuleC2("Module C2: Raw Signals to Reco Signals",
                           "Build Reco Signals from Raw Signals",
                           "raw.sig.root", "reco.sig.root");
    });
    generatorChain->push_back([](){
        return new ModuleC3("Module C3: Reco Signals to Phys Signals",
                           "Build Physical Signals from Reco Signals",
                           "reco.sig.root", "phys.sig.root");
    });
    generatorChain->push_back([](){
        return new ModuleD("Module D: Phys Sig to Phys Hit",
                           "Build Hits from paired Phys Signals",
                           "phys.sig.root", "phys.hit.root");
    });
    generatorChain->push_back([](){
        return new ModuleE("Module E: Phys Hit to Phys Eve",
                           "Build LOR-s from paired Phys Hits",
                           "phys.hit.root", "phys.eve.root");
    });
    manager.AddTaskGeneratorChain(generatorChain);

  manager.Run();

}
