/**
 * @file JPetScopeReader.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 */


#include "./JPetScopeReader.h"

#include <sstream>

#include "../JPetSignal/JPetSignal.h"
#include "../../JPetLoggerInclude.h"

JPetScopeReader::JPetScopeReader(): fInputFile(), fScopeType(), fDate(), fIsFileOpened(false), fSegments(0), fSegmentSize(0) {
}

JPetScopeReader::JPetScopeReader(const char* filename): fInputFile(), fScopeType(), fDate(), fIsFileOpened(false), fSegments(0), fSegmentSize(0) {
  OpenFile(filename);
  ReadHeader();
}

JPetScopeReader::~JPetScopeReader() {
}

void JPetScopeReader::OpenFile(const char* filename) {
  
  if (fIsFileOpened) CloseFile();

  fInputFile.open(filename);

  if (fInputFile.is_open()) {
    fIsFileOpened = true;
  } else {
    ERROR("Error: cannot open file");
  }
}

void JPetScopeReader::CloseFile() {
  if (fIsFileOpened) {
    fInputFile.close();
    fIsFileOpened = false;
    fSegmentSize = 0;
  }
}

void JPetScopeReader::ReadHeader() {

//  std::stringstream buf;
  std::string tmp;

  if (fIsFileOpened) {

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

JPetSignal* JPetScopeReader::ReadData() {
  
  JPetSignal* sig = new JPetSignal();

  float value, threshold;

  for (int i = 0; i < fSegmentSize; ++i) {
    
    JPetSigCh sigCh;
    
    fInputFile >> value >> threshold;

    sigCh.SetValue(value * 1000000000000); // file holds time in seconds, while SigCh requires it in picoseconds
    sigCh.SetThreshold(threshold * 1000);  // file holds thresholds in volts, while SigCh requires it in milivolts
    if (i < fSegmentSize/2) sigCh.SetType(JPetSigCh::EdgeType::Leading);
    else sigCh.SetType(JPetSigCh::EdgeType::Trailing);

    sig->AddPoint(sigCh);
  }

  return sig;
}
