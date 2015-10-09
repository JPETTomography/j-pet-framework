/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetTaskLoader.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Class loads user task and execute in a loop of events
 */

#ifndef _JPETTASKLOADER_H_
#define _JPETTASKLOADER_H_

#include "../../framework/JPetTaskIO/JPetTaskIO.h"
#include <TNamed.h>

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

//#define MODULE_VERSION 1

/// 
class JPetTaskLoader: public JPetTaskIO, public TNamed
{
public:
  JPetTaskLoader() {}
  JPetTaskLoader(const char* name, const char* title,
                 const char* in_file_type,
                 const char* out_file_type,
                 JPetTask* taskToExecute);

  virtual void init(const JPetOptions::Options& opts); /// Overloading JPetTaskIO init
  virtual ~JPetTaskLoader();
protected:
  std::string generateProperNameFile(const std::string& srcFilename, const std::string& fileType) const;
  std::string getBaseFileName(const std::string& srcName) const;

  std::string fInFileType;
  std::string fOutFileType;
  //ClassDef(JPetTaskLoader, MODULE_VERSION );

};

#endif
