#include "./JPetMacroLoader.h"

#include "../../JPetLoggerInclude.h"

#include <TROOT.h>
#include <TSystem.h>

#include <iostream>
using namespace std;

ClassImp(JPetMacroLoader);

JPetMacroLoader::JPetMacroLoader(const char* name, const char* filename): fEvent(0), fEventNb(0) {
  
  //if(gSystem->Load("../../libJPetFramework.so")>=0) {
  //  INFO("Loaded shared lib.");
  //} else {
  //  INFO("Error loading shared lib.");
  //}

  gROOT->LoadMacro(filename);
  fEventNb = gROOT->ProcessLine("GetEventNb()");
  INFO(Form("Number of events in macro: %lld",fEventNb));
}

JPetMacroLoader::~JPetMacroLoader() {
}

void JPetMacroLoader::CreateInputObjects(const char* inputFilename) {
  gROOT->ProcessLine(Form("CreateInputObjects(%s)",inputFilename));
}

void JPetMacroLoader::CreateOutputObjects(const char* outputFilename) {
  gROOT->ProcessLine(Form("CreateOutputObjects(%s)",outputFilename));
}

void JPetMacroLoader::Exec() {
  gROOT->ProcessLine(Form("Exec(%lld)",fEvent));
  fEvent++;
}

void JPetMacroLoader::Terminate() {
}

