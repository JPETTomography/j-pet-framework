/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetTSlotUnpReader.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief reads data from tslot.unp file, which contains raw data unpacked and saved into Tree format.
 */ 

#ifndef JPETTSLOTUNPREADER_H 
#define JPETTSLOTUNPREADER_H 

#include "../JPetReader/JPetReader.h"
#include <cassert> 

class TFile;
class TTree;
class Event;

class JPetTSlotUnpReader: public JPetReader {
 public:
  JPetTSlotUnpReader();
  JPetTSlotUnpReader(const char* filename);
  ~JPetTSlotUnpReader(); 
  void OpenFile(const char* filename);
  void CloseFile();
  long long GetEntries() const; 
  int GetEntry(int number);
  inline Event* GetEvent() 
  { 
    assert(fEvent); 
    return fEvent;
  }
  inline  Event* GetEvent(int number) 
  { 
    GetEntry(number); 
    return GetEvent();
  }
 private:
  TFile* fInputFile;
  TTree* fTree;
  Event* fEvent; // object to which event is write in
};
#endif /*  !JPETTSLOTUNPREADER_H */
