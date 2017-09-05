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
 *  @file JPetTaskLoader.h
 *  @brief Class loads user task and execute in a loop of events
 */

#ifndef _JPETTASKLOADER_H_
#define _JPETTASKLOADER_H_

#include "../JPetTaskIO/JPetTaskIO.h"

class JPetTaskLoader: public JPetTaskIO
{
public:
  JPetTaskLoader() {}
  JPetTaskLoader(const char* in_file_type,
                 const char* out_file_type,
                 JPetTask* taskToExecute);

  virtual bool init(const JPetOptions::Options& opts) override;
  virtual ~JPetTaskLoader();
protected:
  std::string generateProperNameFile(const std::string& srcFilename, const std::string& fileType) const;

  /**
   * @brief Strips the framework file "extension" from full file path
   *
   * The "extension" can be composed of multiple parts, dot-separated.
   * The extension carries information not only about file type but also
   * about types of the objects within the ROOT file.
   * Everything following the first dot in the file name (but not in the file
   * path) is treated as an extension.
   *
   * Example:
   * ./data/somefile.phys.sig.root
   * the extension is "phys.sig.root"
   *
   */
  std::string getBaseFilePath(const std::string& srcName) const;

  std::string fInFileType;
  std::string fOutFileType;
  //ClassDef(JPetTaskLoader, MODULE_VERSION );

};

#endif
