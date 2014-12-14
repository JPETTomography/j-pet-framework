/**
 * @file JPetScopeReader.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 * @brief Class for reading ASCII Oscilloscope data into JPetScopeReader structure.
 */

#ifndef _JPETSCOPEREADER_H_
#define _JPETSCOPEREADER_H_

#include <cstdio>
#include <fstream>
#include <string>

#include "../JPetSignal/JPetSignal.h"

class JPetScopeReader {
  
  public:

  JPetScopeReader();
  JPetScopeReader(const char* filename);

  virtual ~JPetScopeReader();

  JPetSignal* generateSignal (const char* filename);
    
  //inline int getSegments() const {return fSegments;}
  inline int getSegmentSize() const {return fSegmentSize;}
  inline bool isFileOpen() const {if(fInputFile==0) return false; else return true;}
  
  inline void setPrintFile (bool print = true) {fPrintFile = print;}
  inline void setPMID(int PMID) {fPMID = PMID;}

  private:

  void openFile(const char* filename);
  void closeFile();
  void readHeader();
  JPetSignal* readData();

  FILE* fInputFile;

  std::string fScopeType;
  std::string fDate;
  std::string fTime;
  std::string fFilename;

  bool fPrintFile;

  int fPMID;
  //int fSegments;
  int fSegmentSize;
  
};

#endif
