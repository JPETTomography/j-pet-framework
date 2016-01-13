#include "./JPetAnalysisModuleA.h"

#include <JPetSigCh/JPetSigCh.h>
#include <JPetSignal/JPetSignal.h>

#include <vector>

#include <TSystem.h>


using namespace std;

ClassImp(JPetAnalysisModuleA);

JPetAnalysisModuleA::JPetAnalysisModuleA():
  JPetAnalysisModule(),
  fEventNb(0)
{
  gSystem->Load("libTree");
}

JPetAnalysisModuleA::JPetAnalysisModuleA(const char* name, const char* title):
  JPetAnalysisModule(name, title),
  fEventNb(0)
{
  gSystem->Load("libTree");
}

JPetAnalysisModuleA::~JPetAnalysisModuleA()
{
}

void JPetAnalysisModuleA::createInputObjects(const char* inputFilename)
{
}

void JPetAnalysisModuleA::createOutputObjects(const char* outputFilename)
{
}

void JPetAnalysisModuleA::exec()
{
  std::cout << "exec" << std::endl;
}

void JPetAnalysisModuleA::terminate()
{
}
