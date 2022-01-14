/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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

#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetProgressBarManager/JPetProgressBarManager.h"
#include "./JPetStatistics/JPetStatistics.h"
#include "./JPetTask/JPetTask.h"
#include "./JPetTaskIO/JPetInputHandler.h"
#include "./JPetTaskIO/JPetInputHandlerROOT.h"
#include "./JPetTaskIO/JPetOutputHandler.h"
#include "./JPetTaskInterface/JPetTaskInterface.h"
#include <memory>
#include <string>

class JPetReader;
class JPetTreeHeader;
class JPetStatistics;

/**
 * @brief Helper structure to encapsulate some fields
 */
struct TaskIOFileInfo
{
  TaskIOFileInfo(const std::string& inType, const std::string& outType, const std::string& outFullPath, bool resetOutPath)
      : fInFileType(inType), fOutFileType(outType), fOutFileFullPath(outFullPath), fResetOutputPath(resetOutPath){};
  std::string fInFileType;
  std::string fOutFileType;
  std::string fOutFileFullPath;
  bool fResetOutputPath{false};
};

/**
 * @brief Class representing computing task with input/output operations.
 * It is not meant to be used directly, rather used as specialized classes
 * that must provide an implementation of the method run().
 */
class JPetTaskIO : public JPetTask
{
public:
  JPetTaskIO(const char* name = "", const char* in_file_type = "", const char* out_file_type = "");
  virtual ~JPetTaskIO();
  virtual bool init(const JPetParams& inOptions) override;
  virtual bool run(const JPetDataInterface& inData) = 0;
  virtual bool terminate(JPetParams& outOptions) override;
  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  void displayProgressBar(std::string taskName, int currentEventNumber, int numberOfEvents) const;
  virtual JPetParams mergeWithExtraParams(const JPetParams& originalParams, const JPetParams& extraParams) const;
  void setParams(const JPetParams& opts);
  JPetParams getParams() const;
  bool isOutput() const;
  bool isInput() const;

protected:
  virtual std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(const jpet_options_tools::OptsStrAny options) const;
  virtual bool createInputObjects(const char* inputFilename);
  virtual bool createOutputObjects(const char* outputFilename);
  const JPetParamBank& getParamBank();
  JPetParamManager& getParamManager();
  std::string getFirstSubTaskName() const;
  TaskIOFileInfo fTaskInfo;
  bool fIsOutput = true;
  bool fIsInput = true;
  JPetParams fParams;
  JPetTreeHeader* fHeader{nullptr};
  std::unique_ptr<JPetStatistics> fStatistics{nullptr};
  std::map<std::string, std::unique_ptr<JPetStatistics>> fSubTasksStatistics;
  std::unique_ptr<JPetOutputHandler> fOutputHandler{nullptr};
  std::unique_ptr<JPetInputHandler> fInputHandler{nullptr};
  JPetProgressBarManager fProgressBar;

private:
  JPetTaskIO(const JPetTaskIO&);
  void operator=(const JPetTaskIO&);
};
#endif /* !JPETTASKIO_H */
