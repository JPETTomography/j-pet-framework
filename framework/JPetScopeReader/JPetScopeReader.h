/**
 * @file JPetScopeReader.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 * @brief Class for reading ASCII Oscilloscope data into JPetScopeReader structure.
 */

#ifndef _JPETSCOPEREADER_H_
#define _JPETSCOPEREADER_H_

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
  inline bool isFileOpen() const {return fIsFileOpen;}

  inline void setPMID(int PMID) {fPMID = PMID;}

  private:

  void openFile(const char* filename);
  void closeFile();
  void readHeader();
  JPetSignal* readData();

  std::ifstream fInputFile;

  std::string fScopeType;
  std::string fDate;
  std::string fTime;
  std::string fFilename;

  bool fIsFileOpen;

  int fPMID;
  //int fSegments;
  int fSegmentSize;
  
};

#endif
