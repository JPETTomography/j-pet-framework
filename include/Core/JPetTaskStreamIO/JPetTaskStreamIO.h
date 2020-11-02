/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTaskStreamIO.h
 */

#ifndef JPETTASKSTREAMIO_H
#define JPETTASKSTREAMIO_H

#include "./JPetTaskIO/JPetTaskIO.h"

/**
 * @brief Class representing a stream of computing tasks (subtasks),
 * executed subsequently for every set of events (JPetTimeWindow object)
 * so that input and output is used only for the first and last task
 * in the stream.
 *
 * This class only overrides the "run" method of its base JPetTaskIO.
 */
class JPetTaskStreamIO: public JPetTaskIO
{
public:

  JPetTaskStreamIO(const char* name = "", const char* in_file_type = "", const char* out_file_type = "");
  virtual bool run(const JPetDataInterface& inData) override;
  virtual ~JPetTaskStreamIO();

protected:

private:
};
#endif /* !JPETTASKSTREAMIO_H */
