/**
 *  @copyright Copyright (c) 2015, Wojciech Krzemien
 *  @file JPetCommonAnalysisModuleT.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETCOMMONANALYSISMODULET_H 
#define JPETCOMMONANALYSISMODULET_H 
#include "../JPetAnalysisModuleT/JPetAnalysisModuleT.h"
#include <THashTable.h>
#include <TH1F.h>
#include <TH2F.h>


class JPetCommonAnalysisModuleT: public JPetAnalysisModuleT
{
 public:
  JPetCommonAnalysisModuleT();
  virtual ~JPetCommonAnalysisModuleT();
};
#endif /*  !JPETCOMMONANALYSISMODULET_H */
