/**
 *  @file JPetTreeHeader.cpp
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 */

#include "JPetTreeHeader.h"
#include "../CommonTools/CommonTools.h"

ClassImp(JPetTreeHeader);

JPetTreeHeader::JPetTreeHeader():
  fRunNo(-1),
  fSourcePosition(-1),
  fBaseFilename("filename not set")
{
}


JPetTreeHeader::JPetTreeHeader(int run):
  fRunNo(run),
  fSourcePosition(-1),
  fBaseFilename("filename not set")
{
}

TString JPetTreeHeader::stringify() const
{
  TString tmp;
  tmp.Append("-----------------------------------------------------------------\n");
  tmp.Append("------------------------- General Info --------------------------\n");
  tmp.Append("-----------------------------------------------------------------\n");
  tmp.Append( "Run number              : " ).Append( CommonTools::Itoa(fRunNo)).Append("\n");
  tmp.Append( "Base file name          : " ).Append( getBaseFileName() ).Append("\n");
  tmp.Append( "Source (if any) position: " ).Append( Form("%lf",getSourcePosition()) ).Append("\n");
  tmp.Append("-----------------------------------------------------------------\n");
  tmp.Append("-------------- Processing history (oldest first)-----------------\n");
  tmp.Append("-----------------------------------------------------------------\n");
  // iterate over all stages of processing history
  for (int i = 0; i < getStagesNb(); i++ ) {
    const ProcessingStageInfo & info = getProcessingStageInfo(i);
    tmp.Append( "Module Name         : " ).Append( info.fModuleName ).Append("\n");
    tmp.Append( "Module desc.        : " ).Append( info.fModuleDescription ).Append("\n");
    tmp.Append( "Module version      : " ).Append( CommonTools::Itoa( info.fModuleVersion ) ).Append("\n");
    tmp.Append( "Started processing  : " ).Append( info.fCreationTime ).Append("\n");
    tmp.Append("-----------------------------------------------------------------\n");
  }
  
  return tmp;
}

int JPetTreeHeader::addStageInfo(TString p_name, TString p_title, int p_version, TString p_time_stamp )
{
  ProcessingStageInfo stage;
  stage.fModuleName = p_name;
  stage.fModuleDescription = p_title;
  stage.fModuleVersion = p_version;
  stage.fCreationTime = p_time_stamp;
  fStages.push_back( stage );
}

