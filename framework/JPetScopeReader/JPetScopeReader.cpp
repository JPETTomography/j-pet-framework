/**
 * @file JPetScopeReader.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 */


#include "./JPetScopeReader.h"

#include <iostream>
#include <TString.h>

#include "../JPetSignal/JPetSignal.h"
#include "../../JPetLoggerInclude.h"

using namespace std;

JPetScopeReader::JPetScopeReader(): fInputFile(), fScopeType(), fDate(), fIsFileOpen(false), fPrintFile(false), fPMID(0), fSegmentSize(0) {
}

JPetScopeReader::JPetScopeReader(const char* filename): fInputFile(), fScopeType(), fDate(), fIsFileOpen(false), fPrintFile(false), fPMID(0), fSegmentSize(0) {
  openFile(filename);
  readHeader();
}

JPetScopeReader::~JPetScopeReader() {
}

JPetSignal* JPetScopeReader::generateSignal(const char* filename) {
  openFile(filename);
  readHeader();
  JPetSignal* sig;

  if (fIsFileOpen) sig = readData();
  else sig = 0;

  closeFile();
  return sig;
}

void JPetScopeReader::openFile(const char* filename) {
  
  if (fIsFileOpen) closeFile();

  fInputFile.open(filename);
  fFilename = filename;

  if (fInputFile.is_open()) {
    fIsFileOpen = true;
  } else {
    ERROR(Form("Error: cannot open file %s", fFilename.c_str()));
  }
}

void JPetScopeReader::closeFile() {
  if (fIsFileOpen) {
    fInputFile.close();
    fIsFileOpen = false;
    fSegmentSize = 0;
  }
}

void JPetScopeReader::readHeader() {

//  std::stringstream buf;
  string tmp;

  if (fIsFileOpen) {

    fInputFile >> fScopeType;
    fInputFile >> tmp;
    fInputFile >> tmp;

    fInputFile >> tmp;
    fInputFile >> tmp;
    fInputFile >> tmp;
    fInputFile >> fSegmentSize;

    fInputFile >> tmp;
    fInputFile >> tmp;
    fInputFile >> tmp;

    fInputFile >> tmp;
    fInputFile >> fDate;
    fInputFile >> fTime;
    fInputFile >> tmp;

    fInputFile >> tmp;
    fInputFile >> tmp;

    if (fPrintFile) {
      cout << "Scope type: " << fScopeType << endl;
      cout << "Segment size: " << fSegmentSize << endl;
      cout << "Date and time: " << fDate << " " << fTime << endl;
    }

  }
  
}

JPetSignal* JPetScopeReader::readData() {
  
  JPetSignal* sig = new JPetSignal();

  float value, threshold;

  if (fPrintFile) cout << "value:      " << "threshold:" << endl; 

  for (int i = 0; i < fSegmentSize; ++i) {
    
    JPetSigCh* sigCh = new JPetSigCh();
    
    fInputFile >> value >> threshold;

    if (fPrintFile) cout << value << " " << threshold << endl;;

    if (fInputFile.fail()) {
      fInputFile.clear();
      fInputFile.ignore(255, '\n');
      ERROR(Form("Non-numerical symbol in file %s at line %d", fFilename.c_str(), i + 6));
    }

    sigCh->setValue(value * 1000000000000); // file holds time in seconds, while SigCh requires it in picoseconds
    sigCh->setThreshold(threshold * 1000);  // file holds thresholds in volts, while SigCh requires it in milivolts
    sigCh->setPMID(fPMID);
    sigCh->setType(JPetSigCh::Leading);

    sig->addPoint(*sigCh);
  }

  return sig;
}
