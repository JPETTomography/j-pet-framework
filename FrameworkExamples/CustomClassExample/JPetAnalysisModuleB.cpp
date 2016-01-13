#include "./JPetAnalysisModuleB.h"

#include <JPetLOR/JPetLOR.h>
#include <JPetHit/JPetHit.h>
#include <JPetSignal/JPetSignal.h>

#include <vector>

#include <TSystem.h>

using namespace std;

ClassImp(JPetAnalysisModuleB);

JPetAnalysisModuleB::JPetAnalysisModuleB():JPetAnalysisModule(), fEventNb(0), fWriter(NULL) {
  gSystem->Load("libTree");
}

JPetAnalysisModuleB::JPetAnalysisModuleB(const char* name, const char* title):JPetAnalysisModule(name, title), fEventNb(0), fWriter(NULL) {
  gSystem->Load("libTree");
}

JPetAnalysisModuleB::~JPetAnalysisModuleB() {
  if (fWriter != NULL) delete fWriter;
}

void JPetAnalysisModuleB::createInputObjects(const char* inputFilename) {
  
  const char* filename = "./phys.sig.root";
  fReader = new JPetReader(filename);
  fEventNb = fReader->getEntries();

};

void JPetAnalysisModuleB::createOutputObjects(const char* outputFilename) {
  const char* filename = "phys.eve.root";
  fWriter = new JPetWriter(filename);
}

void JPetAnalysisModuleB::exec() {
  
  JPetSignal* signal1;
  JPetSignal* signal2;
  
  JPetHit* hit1;
  JPetHit* hit2;

  JPetLOR* event;
    
  fReader->getEntry(fEvent++);
  signal1 = (JPetSignal*)(&(fReader->getData()));
  fReader->getEntry(fEvent++);
  signal2 = (JPetSignal*)(&(fReader->getData()));

  hit1 = new JPetHit();
  hit1->SetSignals(signal1,signal2);
 
  fReader->getEntry(fEvent++);
  signal1 = (JPetSignal*)(&(fReader->getData()));
  fReader->getEntry(fEvent++);
  signal2 = (JPetSignal*)(&(fReader->getData()));

  hit2 = new JPetHit();
  hit2->SetSignals(signal1,signal2);

  event = new JPetLOR();
  event->SetFirstHit(hit1);
  event->SetSecondHit(hit2);
 
  fWriter->write(*event);
}

void JPetAnalysisModuleB::terminate() {
  fReader->closeFile();
  fWriter->closeFile();
}
