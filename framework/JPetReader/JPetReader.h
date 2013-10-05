/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetReader.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETREADER_H 
#define JPETREADER_H 

#include "TFile.h"
#include "TNamed.h"

#include <string>

class JPetReader {

  public:

  JPetReader();
  virtual ~JPetReader();
  virtual bool OpenFile(const char* filename);
  virtual void CloseFile();
  virtual long long GetEntries()const = 0;
  virtual int GetEntry(int number) = 0;

  protected:
  
  static TFile *fFile;

};
#endif /*  !JPETREADER_H */
