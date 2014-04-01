#include "./JPetMacroLoader.h"

#include "../../JPetLoggerInclude.h"

#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>

#include <iostream>
using namespace std;

ClassImp(JPetMacroLoader);

JPetMacroLoader::JPetMacroLoader(const char* name, const char* filename): fEvent(0), fEventNb(0) {
  

  gROOT->LoadMacro(filename);
  fEventNb = gROOT->ProcessLine("GetEventNb()");
  INFO(Form("Number of events in macro: %lld",fEventNb));
}

JPetMacroLoader::~JPetMacroLoader() {
}

void JPetMacroLoader::CreateInputObjects(const char* inputFilename) {
  TString inFile;
  if (inputFilename == NULL) inFile.Form("CreateInputObjects(0)");
  else  inFile.Form("CreateInputObjects(\"%s\")", inputFilename);
  const char* c = inFile;
  gROOT->ProcessLine(c);
}

void JPetMacroLoader::CreateOutputObjects(const char* outputFilename) {
  TString outFile;
  if (outputFilename == NULL) outFile.Form("CreateOutputObjects(0)");
  else outFile.Form("CreateOutputObjects(\"%s\")", outputFilename);
  const char* c = outFile;
  gROOT->ProcessLine(c);
}

void JPetMacroLoader::Exec() {
  gROOT->ProcessLine(Form("Exec(%lld)",fEvent));
  fEvent++;
}

void JPetMacroLoader::Terminate() {
}

