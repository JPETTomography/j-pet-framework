/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetTSlotRawHeader.cpp
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 */ 

#include "JPetTSlotRawHeader.h"

ClassImp(JPetTSlotRawHeader);

JPetTSlotRawHeader::JPetTSlotRawHeader( int run, TString producer, int version ):
  JPetTreeHeader(run, producer, version) {
}

int JPetTSlotRawHeader::addHLDinfo(TString name, int id, 
                               double startT, int firstEvt, int nEvts){

  fHLDnames.push_back( name );
  fHLDids.push_back( id );
  fHLDstartTimes.push_back( startT );
  fHLDnEvts.push_back( nEvts );
  fHLDfirstEvt.push_back( firstEvt );

  return fHLDnames.size();
}

TString JPetTSlotRawHeader::getHLDname(int no) const {
  return fHLDnames.at( no );
}

int JPetTSlotRawHeader::getHLDid(int no) const {
  return fHLDids.at( no );
}

int JPetTSlotRawHeader::getHLDnEvts(int no) const {
  return fHLDnEvts.at( no );
}

int JPetTSlotRawHeader::getHLDfirstEvt(int no) const {
  return fHLDfirstEvt.at( no );
}

double JPetTSlotRawHeader::getHLDstartTime(int no) const {
  return fHLDstartTimes.at( no );
}


TString JPetTSlotRawHeader::Stringify() const{
  TString tmp = JPetTreeHeader::Stringify();
  tmp.Append( "number if HLD files :  " ).Append( TString::Itoa( fHLDnames.size(), 10.));
  tmp.Append( "\nList of HLD files:\n" );
  tmp.Append("-----------------------------------------------------------------\n");
  for(int i=0; i<fHLDnames.size(); i++ ){
    tmp.Append( "file : " ).Append( getHLDname(i) ).Append("   ");
    tmp.Append( "id : " ).Append( TString::Itoa( getHLDid(i), 10.) ).Append("\n");
    tmp.Append( "start time : " ).Append( Form("%lf", getHLDstartTime(i) ) ).Append("\n");
    tmp.Append( "first event : " ).Append( TString::Itoa( getHLDfirstEvt(i), 10) ).Append("   ");
    tmp.Append( "number of events : " ).Append( TString::Itoa( getHLDnEvts(i), 10.) ).Append("\n");
    tmp.Append("-----------------------------------------------------------------\n");
  }

  return tmp;
}
