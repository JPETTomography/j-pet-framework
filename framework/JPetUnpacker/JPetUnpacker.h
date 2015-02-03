/**
 * @file JPetUnpacker.h
 * @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 * @copyright Copyright (c) 2014, J-PET collaboration
 * @brief facade for Unpacker program which unpacks raw data to root files
 */

#ifndef _JPETUNPACKER_H_
#define _JPETUNPACKER_H_

//#include <cstddef>
#include <string>
#include <TObject.h>
#include "./Unpacker2/Unpacker2.h"

class Unpacker2;

class JPetUnpacker: public TObject
{
 public:

  JPetUnpacker();
  ~JPetUnpacker();
  bool exec();
  inline int getEventsToProcess() const { return fEventsToProcess; }
  inline std::string getHldFile() const { return fHldFile; }
  inline std::string getCfgFile() const { return fCfgFile; }
  void setParams(const std::string& hldFile, int numOfEvents = 100000000, const std::string& cfgFile = "conf_trb3.xml");

  ClassDef(JPetUnpacker, 1);

 private:
  Unpacker2* fUnpacker;  
  int fEventsToProcess;
  std::string fHldFile;
  std::string fCfgFile;
};

#endif
