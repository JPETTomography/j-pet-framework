/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetReader.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETREADER_H 
#define JPETREADER_H 

#include <string>

class JPetReader {
 public:
  JPetReader();
  virtual ~JPetReader();
  virtual void OpenFile(const char* filename) = 0;
  virtual void CloseFile() = 0;
  virtual long long GetEntries()const = 0; 
  virtual int GetEntry(int number) = 0;
};
#endif /*  !JPETREADER_H */
