/**
 *  @file JPetTreeHeader.cpp
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 */

#include "JPetTreeHeader.h"

ClassImp(JPetTreeHeader);

JPetTreeHeader::JPetTreeHeader( int run, TString producer, int version ):
  fRunNo(run), fProducerName(producer), fProducerVersion(version)
{
}

TString JPetTreeHeader::Stringify() const
{
  TString tmp;
  tmp.Append( "Data file info:" );
  tmp.Append( "\nrun number          :  " ).Append( TString::Itoa( fRunNo, 10.));
  tmp.Append( "\nproducer name       :  " ).Append( fProducerName );
  tmp.Append( "\nproducer version    :  " ).Append( TString::Itoa( fProducerVersion, 10.));
  tmp.Append("\n");
  return tmp;
}
