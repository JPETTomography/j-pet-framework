/**
 *  @copyright Copyright (c) 2015, Wojciech Krzemien
 *  @file JPetTaskOptions.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */

#ifndef JPETTASKOPTIONS_H
#define JPETTASKOPTIONS_H

#include <string>
#include <map>
#include "../CommonTools/CommonTools.h"

class JPetTaskOptions
{

 public:
  enum FileType  {kNoType, kRaw, kHld, kPhysEve, kPhysHit, kPhysSig,
                  kRawSig, kRecoSig, kTslotCal, kTslotRaw};
  typedef std::map<std::string, std::string> Options;
  
  JPetTaskOptions();
  explicit  JPetTaskOptions(const Options& opts);

  bool areCorrect(const Options& opts) const;
  const char* getInputFile() const { return fOptions.at("inputFile").c_str();}
  const char* getOutputFile() const { return fOptions.at("outputFile").c_str();}
  long long getFirstEvent() const { return std::stoll(fOptions.at("firstEvent"));}
  long long getLastEvent() const { return std::stoll(fOptions.at("lastEvent"));}
  bool isProgressBar() const { return CommonTools::to_bool(fOptions.at("progressBar"));}
  FileType getInputFileType() const {
    auto option = fOptions.at("inputFileType");
    return fStringToFileType.at(option);
  }
  FileType getOutputFileType() const {
    auto option = fOptions.at("outputFileType");
    return fStringToFileType.at(option); 
  }
 protected:
  void setOptions(const Options& opts) { fOptions = opts;}
  void setStringToFileTypeConversion();
  Options fOptions;
  std::map<std::string, JPetTaskOptions::FileType> fStringToFileType;

};
#endif /*  !JPETTASKOPTIONS_H */
