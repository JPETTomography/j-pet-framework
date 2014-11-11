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

  void OpenFile(const char* filename);
  void CloseFile();
  void ReadHeader();
  JPetSignal* ReadData();
  

  inline int GetSegments() const {return fSegments;}
  inline int GetSegmentSize() const {return fSegmentSize;}
  inline bool IsFileOpened() const {return fIsFileOpened;}

  private:

  std::ifstream fInputFile;

  std::string fScopeType;
  std::string fDate;
  std::string fTime;

  bool fIsFileOpened;

  int fSegments;
  int fSegmentSize;
  
};

#endif
