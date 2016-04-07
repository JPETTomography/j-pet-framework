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
 *  @file RunData.h
 */

#ifndef RUN_DATA_H
#define RUN_DATA_H

#include <string>
#include <fstream>


namespace DB
{

namespace DATA
{

class RunData
{
public:
  RunData(void);
  RunData(std::string p_runStart, std::string p_filePath, std::string p_runDescription, std::string p_information);
  RunData(const RunData &p_runDataObject);
  RunData& operator=(const RunData &p_runDataObject);
  bool operator==(const RunData &p_runDataObject);
  bool operator!=(const RunData &p_runDataObject);
  virtual ~RunData(void);

protected:
  std::string m_runStart;
  std::string m_filePath;
  std::string m_runDescription;
  std::string m_information;

public:
  virtual std::string runStart(void) const;
  virtual std::string filePath(void) const;
  virtual std::string runDescription(void) const;
  virtual std::string information(void) const;

  friend std::ostream& operator<< (std::ostream &p_stream, RunData const &p_runDataObject);
  friend std::ofstream& operator<< (std::ofstream &p_ofstream, RunData const &p_runDataObject);
};

} // namespace DATA

} // namespace DB

#endif // RUN_DATA_H
