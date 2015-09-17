/**
 *  @copyright Copyright (c) 2015, Wojciech Krzemien
 *  @file JPetAnalysisModuleT.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETANALYSISMODULET_H 
#define JPETANALYSISMODULET_H 
#include "../JPetTaskIO/JPetTaskIO.h"
#include <THashTable.h>
#include <TH1F.h>
#include <TH2F.h>


class JPetAnalysisModuleT: public JPetTaskIO
{
 public:
  JPetAnalysisModuleT();
  virtual ~JPetAnalysisModuleT();

  int addStatsObject(TObject * statObj);
  const THashTable * getStatsObjects() const;

  // more convenient methods to access histograms from the statsObjects list
  TH1F * getHisto1D(const char * name);

  TH2F * getHisto2D(const char * name);

  TObject * getStatsObject(const char * name);
 protected:
  THashTable fStats; ///< a hash table to store all objects for statistics of the processing, i.e. histograms
};
#endif /*  !JPETANALYSISMODULET_H */
