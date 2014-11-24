#include "./JPetMacroLoader.h"

#include "../../JPetLoggerInclude.h"

#include <TROOT.h>
#include <TSystem.h>

#include <iostream>
using namespace std;

ClassImp(JPetMacroLoader);

JPetMacroLoader::JPetMacroLoader(const char* name, const char* filename): fEvent(0), fEventNb(0) {
  

  gROOT->LoadMacro(filename);
  fEventNb = gROOT->ProcessLine("getEventNb()");
  INFO(Form("Number of events in macro: %lld",fEventNb));
}

JPetMacroLoader::~JPetMacroLoader() {
}

void JPetMacroLoader::createInputObjects(const char* inputFilename) {

  TString inFile;
  if (inputFilename == NULL) inFile.Form("createInputObjects(0)");
  else  inFile.Form("createInputObjects(\"%s\")", inputFilename);
  const char* c = inFile;
  gROOT->ProcessLine(c);
}

void JPetMacroLoader::createOutputObjects(const char* outputFilename) {
  TString outFile;
  if (outputFilename == NULL) outFile.Form("createOutputObjects(0)");
  else outFile.Form("createOutputObjects(\"%s\")", outputFilename);
  const char* c = outFile;
  gROOT->ProcessLine(c);
}

void JPetMacroLoader::exec() {
  gROOT->ProcessLine(Form("exec(%lld)",fEvent));
  fEvent++;
}

void JPetMacroLoader::terminate() {
}

