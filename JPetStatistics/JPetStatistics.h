/**
 *  @file JPetStatustics.h
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2015, J-PET collaboration
 */
#ifndef _JPET_STATISTICS_H_
#define _JPET_STATISTICS_H_

#include <THashTable.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <map>

/**
 * @brief An class for storing statistics of the processing (e.g histograms and counters) during execution of a JPetTask 
 *
 */

class JPetStatistics: public TObject{
  
 public:
  
  void createHistogram(TObject * object);
  TH1F & getHisto1D(const char * name);
  TH2F & getHisto2D(const char * name);
  void createCounter(const char * name);
  double & getCounter(const char * name);

  const THashTable * getHistogramsTable() const;
  
  ClassDef(JPetStatistics,1); 
    
 protected:
  THashTable fHistos;
  std::map<TString, double> fCounters;
 
};

#endif
