/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetTSlotRawHeader.h
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @brief Encapsulates information from the top-level of JPet data files as defined in Report 19, table 37. Intended to be stored in a ROOT file in the UserInfo list of a TTree it describes. Use JPetWriter::WriteHeader() and JPetReader::GetHeader() for this.
 */ 

#ifndef _JPET_TSLOT_RAW_HEADER_H_
#define _JPET_TSLOT_RAW_HEADER_H_

#include "JPetTreeHeader.h"
#include <vector>

#include "TString.h"


class JPetTSlotRawHeader : public JPetTreeHeader{
  
 public:
  JPetTSlotRawHeader(){};  
  JPetTSlotRawHeader( int run, TString producer = "", int version = -1 );
  int addHLDinfo(TString name, int id, double startT, int firstEvt, int nEvts);
  int getNoHLDfiles(){ return fHLDnames.size(); } 
  
  TString getHLDname(int no) const;
  int getHLDid(int no) const;
  int getHLDnEvts(int no) const;
  int getHLDfirstEvt(int no) const;
  double getHLDstartTime(int no) const;

  TString Stringify() const;

  ClassDef(JPetTSlotRawHeader,1);
  

 private:
  std::vector<TString> fHLDnames;
  std::vector<int> fHLDids;
  std::vector<int> fHLDnEvts;
  std::vector<int> fHLDfirstEvt;
  std::vector<double> fHLDstartTimes;
  
};

#endif
