/**
 * @file JPetScopeReader.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 */


#include "./JPetScopeReader.h"

#include <iostream>
#include <TString.h>

#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../../JPetLoggerInclude.h"

using namespace std;

const double ks2ps = 1.0e+12;
const double kV2mV = 1.0e+3;
const int kbuflen = 256;

JPetScopeReader::JPetScopeReader(): fInputFile(0), fScopeType(), fDate(), fPrintFile(false), fPMID(0), fSegmentSize(0) {
}

//JPetScopeReader::JPetScopeReader(const char* filename): fInputFile(0), fScopeType(), fDate(), fPrintFile(false), fPMID(0), fSegmentSize(0) {
//  openFile(filename);
//  readHeader();
//}

JPetScopeReader::~JPetScopeReader() {
}

JPetPhysSignal* JPetScopeReader::generateSignal(const char* filename) {
  openFile(filename);
  readHeader();
  JPetPhysSignal* sig;

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
  char buf[kbuflen];
  char tmp[kbuflen];

  if (isFileOpen()) {

    fgets(buf, kbuflen, fInputFile);
    sscanf(buf, "%s %*s %*s", tmp);

    fScopeType = tmp;

    fgets(buf, kbuflen, fInputFile);
    sscanf(buf, "%*s %*s %*s %d", &fSegmentSize);

    fgets(buf, kbuflen, fInputFile);
    //sscanf(buf, "%*s %*s %*s");

    fgets(buf, kbuflen, fInputFile);
    sscanf(buf, "%*s %s %s %*s", tmp, tmp + kbuflen/2);

    fDate = tmp;
    fTime = tmp + kbuflen/2;

    fgets(buf, kbuflen, fInputFile);
    //sscanf(buf, "%*s %*s");

    if (fPrintFile) {
      cout << "Scope type: " << fScopeType << endl;
      cout << "Segment size: " << fSegmentSize << endl;
      cout << "Date and time: " << fDate << " " << fTime << endl;
    }

  }
  
}

JPetPhysSignal* JPetScopeReader::readData() {
  
  JPetPhysSignal* sig = new JPetPhysSignal();
  JPetRecoSignal recoSig(fSegmentSize);

  float value, threshold;
  int stat;

  if (fPrintFile) cout << "value:      " << "threshold:" << endl; 

  for (int i = 0; i < fSegmentSize; ++i) {
    
    stat = fscanf(fInputFile, "%f %f\n", &value, &threshold);

    if (fPrintFile) cout << value << " " << threshold << endl;;

    if (stat != 2) {
      ERROR(Form("Non-numerical symbol in file %s at line %d", fFilename.c_str(), i + 6));
      char tmp[kbuflen];
      fgets(tmp, kbuflen, fInputFile);
    }

    float time = value * ks2ps; // file holds time in seconds, while SigCh requires it in picoseconds
    float amplitude = threshold * kV2mV;  // file holds thresholds in volts, while SigCh requires it in milivolts
    //sigCh.setPMID(fPMID);

    recoSig.setShapePoint(time, amplitude);
  }

  sig->setRecoSignal( recoSig );

  return sig;
}
