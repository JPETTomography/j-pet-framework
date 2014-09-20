/**
 *  @file JPetTreeHeader.cpp
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 */

#include "JPetTreeHeader.h"
#include "../CommonTools/CommonTools.h"

ClassImp(JPetTreeHeader);

JPetTreeHeader::JPetTreeHeader( int run, TString producer, int version ):
  fRunNo(run), fProducerName(producer), fProducerVersion(version)
{
}

TString JPetTreeHeader::Stringify() const
{
  TString tmp;
  tmp.Append( "Data file info:" );
  tmp.Append( "\nrun number          :  " ).Append( CommonTools::Itoa(fRunNo));
  tmp.Append( "\nproducer name       :  " ).Append( fProducerName );
  tmp.Append( "\nproducer version    :  " ).Append( CommonTools::Itoa( fProducerVersion));
  tmp.Append("\n");

  tmp.Append( "number of HLD files :  " ).Append( CommonTools::Itoa( fHLDnames.size()));
  tmp.Append( "\nList of HLD files:\n" );
  tmp.Append("-----------------------------------------------------------------\n");
  // iterate over all HLD files
  for (int i = 0; i < fHLDnames.size(); i++ ) {
    tmp.Append( "file : " ).Append( getHLDname(i) ).Append("   ");
    tmp.Append( "id : " ).Append( CommonTools::Itoa( getHLDid(i)) ).Append("\n");
    tmp.Append( "time window width : " ).Append( Form( "%f ps", getHLDwindowWidth(i) ) ).Append("\n");
    tmp.Append( "start time : " ).Append( Form("%lf", getHLDstartTime(i) ) ).Append("\n");
    tmp.Append( "first event : " ).Append( CommonTools::Itoa( getHLDfirstEvt(i)) ).Append("   ");
    tmp.Append( "number of events : " ).Append( CommonTools::Itoa( getHLDnEvts(i)) ).Append("\n");
    tmp.Append("-----------------------------------------------------------------\n");
  }
  
  return tmp;
}


int JPetTreeHeader::addHLDinfo(TString name, int id, int nEvts, float width,
			       int firstEvt, double startT )
{

  fHLDnames.push_back( name );
  fHLDids.push_back( id );
  fHLDwinWidths.push_back( width );
  fHLDstartTimes.push_back( startT );
  fHLDnEvts.push_back( nEvts );
  fHLDfirstEvt.push_back( firstEvt );

  return fHLDnames.size();
}

TString JPetTreeHeader::getHLDname(int no) const
{
  return fHLDnames.at( no );
}

int JPetTreeHeader::getHLDid(int no) const
{
  return fHLDids.at( no );
}

int JPetTreeHeader::getHLDnEvts(int no) const
{
  return fHLDnEvts.at( no );
}

float JPetTreeHeader::getHLDwindowWidth(int no) const{
  return fHLDwinWidths.at( no );
}

int JPetTreeHeader::getHLDfirstEvt(int no) const
{
  return fHLDfirstEvt.at( no );
}

double JPetTreeHeader::getHLDstartTime(int no) const
{
  return fHLDstartTimes.at( no );
}
