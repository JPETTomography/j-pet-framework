/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetTaskIO.h
 */

#ifndef JPETTASKIO_H
#define JPETTASKIO_H

#include "./JPetTaskInterface/JPetTaskInterface.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetStatistics/JPetStatistics.h"
#include "./JPetTask/JPetTask.h"
#include "./JPetProgressBarManager/JPetProgressBarManager.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetTaskIO/JPetOutputHandler.h"
#include <memory>
#include <string>

class JPetReader;
class JPetTreeHeader;
class JPetStatistics;


/**
 * @brief Class representing computing task with input/output operations.
 * In the current implementation the single entry that is read by the reader
 * corresponds to a JPetTimeWindow object.
 */
class JPetTaskIO: public JPetTask
{
public:
  JPetTaskIO(const char* name = "", const char* in_file_type = "", const char* out_file_type = "");
  virtual bool init(const JPetParamsInterface& inOptions) override;
  virtual bool run(const JPetDataInterface& inData) override;
  virtual bool terminate(JPetParamsInterface& outOptions) override;
  virtual ~JPetTaskIO();
  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  void setOptions(const JPetParams& opts);

  inline JPetParams getOptions() const
  {
    return fParams;
  }

  void displayProgressBar(int currentEventNumber, int numberOfEvents) const;

  bool isOutput() const;

protected:
  /// @return (isOK, inputFile, outputFileFullPath, isResetOutputPath) based on provided options. If isOK is set to false, that means that an error has occured.
  virtual std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(const jpet_options_tools::OptsStrAny options) const;
  virtual bool createInputObjects(const char* inputFilename);
  virtual bool createOutputObjects(const char* outputFilename);

  const JPetParamBank& getParamBank();
  JPetParamManager& getParamManager();

  std::tuple<bool, long long, long long, long long> getEventRange(const jpet_options_tools::OptsStrAny& options, JPetReaderInterface* reader);

  std::string fInFileType;
  std::string fOutFileType;
  std::string fOutFileFullPath;
  bool fResetOutputPath;

  bool fIsOutput = true; /// Temporary and very nasty way to mark that the output will be saved.
  int fEventNb = -1; /// @todo is this used anywhere?
  JPetParams fParams;

  std::unique_ptr<JPetReaderInterface> fReader{nullptr};

  JPetTreeHeader* fHeader{nullptr};
  std::unique_ptr<JPetStatistics> fStatistics{nullptr};
  std::map<std::string, std::unique_ptr<JPetStatistics>> fSubTasksStatistics;

  std::unique_ptr<JPetOutputHandler> fOutputHandler{nullptr};

  JPetProgressBarManager fProgressBar;
private:
  JPetTaskIO(const JPetTaskIO&);
  void operator=(const JPetTaskIO&);
};
#endif /*  !JPETTASKIO_H */
