/**
 * @file JPetScopeReader.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 */


#include "./JPetScopeReader.h"

//#include <sstream>

#include "../JPetSignal/JPetSignal.h"
#include "../../JPetLoggerInclude.h"

JPetScopeReader::JPetScopeReader(): fInputFile(), fScopeType(), fDate(), fIsFileOpen(false), fSegments(0), fSegmentSize(0) {
}

JPetScopeReader::JPetScopeReader(const char* filename): fInputFile(), fScopeType(), fDate(), fIsFileOpen(false), fSegments(0), fSegmentSize(0) {
  openFile(filename);
  readHeader();
}

JPetScopeReader::~JPetScopeReader() {
}

void JPetScopeReader::openFile(const char* filename) {
  
  if (fIsFileOpen) closeFile();

  fInputFile.open(filename);

  if (fInputFile.is_open()) {
    fIsFileOpen = true;
  } else {
    ERROR("Error: cannot open file");
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
  std::string tmp;

  if (fIsFileOpen) {

//    getline(fInputFile, tmp); buf << tmp;
//    buf >> fScopeType;
//
//    getline(fInputFile, tmp); buf << tmp;
//    buf >> tmp;
//    buf >> fSegments;
//    buf >> tmp;
//    buf >> fSegmentSize;
//
//    getline(fInputFile, tmp); buf << tmp;
//
//
//    getline(fInputFile, tmp); buf << tmp;
//    buf >> tmp;
//    buf >> fDate;
//    buf >> fTime;
//
//    getline(fInputFile, tmp); buf << tmp;

    fInputFile >> fScopeType;
    fInputFile >> tmp;
    fInputFile >> tmp;

    fInputFile >> tmp;
    fInputFile >> fSegments;
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

    }
  
}

JPetSignal* JPetScopeReader::readData() {
  
  JPetSignal* sig = new JPetSignal();

  float value, threshold;

  for (int i = 0; i < fSegmentSize; ++i) {
    
    JPetSigCh* sigCh = new JPetSigCh();
    
    fInputFile >> value >> threshold;

    sigCh->setValue(value * 1000000000000); // file holds time in seconds, while SigCh requires it in picoseconds
    sigCh->setThreshold(threshold * 1000);  // file holds thresholds in volts, while SigCh requires it in milivolts
    sigCh->setPMID(fPMID);
    sigCh->setType(JPetSigCh::Leading);

    sig->addPoint(*sigCh);
  }

  return sig;
}
