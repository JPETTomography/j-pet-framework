/**
 *  @file JPetTreeHeader.h
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @brief Base class for headers with info on JPet ROOT Trees
 * Encapsulates information from the top-level of JPet data files as defined in Report 19, tables 37+. For each type of data files produced after each level of processing, a new class should inherit from this base class. The TreeHeader objects are intended to be stored in a ROOT file along with a respective TTree which they describe.
 */

#ifndef _JPET_TREE_HEADER_H_
#define _JPET_TREE_HEADER_H_

#include "TObject.h"
#include "TString.h"
#include <iostream>
#include <ostream>

class JPetTreeHeader: public TObject{
  
 public:
  JPetTreeHeader(){};
  JPetTreeHeader( int run, TString producer = "", int version = -1 );
  void Print(Option_t * opt = "") const { std::cout<<this->Stringify(); }
  virtual TString Stringify() const;
  
  TString getProducerName() const { return fProducerName; }
  int getProducerVersion()  const { return fProducerVersion; }
  int getRunNumber()  const { return fRunNo; }

  ClassDef(JPetTreeHeader,1);
  
 protected:
  TString fProducerName;
  int fProducerVersion;
  int fRunNo;
  
}; 


/* ostream& operator<<(ostream& os, const JPetTreeHeader& header){ */
/*   os << header.Stringify(); */
/*   return os; */
/* } */

#endif
