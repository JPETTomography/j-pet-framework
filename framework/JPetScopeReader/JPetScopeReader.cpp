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

JPetScopeReader::JPetScopeReader(): fInputFile(0), fScopeType(), fDate(), fPrintFile(false), fPMID(0), fSegmentSize(0) {
}

JPetScopeReader::JPetScopeReader(const char* filename): fInputFile(0), fScopeType(), fDate(), fPrintFile(false), fPMID(0), fSegmentSize(0) {
  openFile(filename);
  readHeader();
}

JPetScopeReader::~JPetScopeReader() {
}

JPetSignal* JPetScopeReader::generateSignal(const char* filename) {
  openFile(filename);
  readHeader();
  JPetSignal* sig;

  if (isFileOpen()) sig = readData();
  else sig = 0;

  closeFile();
  return sig;
}

void JPetScopeReader::openFile(const char* filename) {

  if (isFileOpen()) closeFile();

  fInputFile = fopen(filename, "r");
  fFilename = filename;

  if (!isFileOpen()) {
    ERROR(Form("Error: cannot open file %s", fFilename.c_str()));
  }
}

void JPetScopeReader::closeFile() {
  if (isFileOpen()) {

    fclose(fInputFile);
    fInputFile = 0;
    fSegmentSize = 0;
  }
}

void JPetScopeReader::readHeader() {

//  std::stringstream buf;
  char buf[256];
  char tmp[256];

  if (isFileOpen()) {

    fgets(buf, 256, fInputFile);
    sscanf(buf, "%s %*s %*s", tmp);

    fScopeType = tmp;

    fgets(buf, 256, fInputFile);
    sscanf(buf, "%*s %*s %*s %d", &fSegmentSize);

    fgets(buf, 256, fInputFile);
    //sscanf(buf, "%*s %*s %*s");

    fgets(buf, 256, fInputFile);
    sscanf(buf, "%*s %s %s %*s", tmp, tmp+128);

    fDate = tmp;
    fTime = tmp+128;

    fgets(buf, 256, fInputFile);
    //sscanf(buf, "%*s %*s");

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
  int stat;

  if (fPrintFile) cout << "value:      " << "threshold:" << endl; 

  for (int i = 0; i < fSegmentSize; ++i) {
    
    JPetSigCh* sigCh = new JPetSigCh();
    
    stat = fscanf(fInputFile, "%f %f\n", &value, &threshold);

    if (fPrintFile) cout << value << " " << threshold << endl;;

    if (stat != 2) {
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
