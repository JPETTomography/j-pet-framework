#include "./JPetUnpacker.h"
#include "./Unpacker2/Unpacker2.h"

ClassImp(JPetUnpacker);

JPetUnpacker::JPetUnpacker():JPetAnalysisModule(), fEventNb(1) {
  
}

JPetUnpacker::JPetUnpacker(const char* name, const char* title):JPetAnalysisModule(name, title), fEventNb(1) {
  
}

JPetUnpacker::~JPetUnpacker() {
}

void JPetUnpacker::CreateInputObjects(const char* inputFilename) {

}

void JPetUnpacker::SetParams(const char* hldFile, const char* cfgFile, int numOfEvents) {
  fHldFile = hldFile;
  fCfgFile = cfgFile;
  fEventsToProcess = numOfEvents;
}

void JPetUnpacker::CreateOutputObjects(const char* outputFilename) {
}

void JPetUnpacker::Exec() {
  Unpacker2* unpacker = new Unpacker2(fHldFile, fCfgFile, fEventsToProcess);
}

void JPetUnpacker::Terminate() {
}
