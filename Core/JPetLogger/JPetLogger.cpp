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
 *  @file JPetLogger.cpp
 */

#include <ctime>
#include <cassert>
#include "./JPetLogger.h"

/*void JPetLogger::dateAndTime()
{
  std::ofstream log(fFileName.c_str(), std::ios_base::app);
  std::streambuf* originalCoutBuffer = 0;
  // we redirect std::cout to a file
  if (fIsLogFile) {
    originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(log.rdbuf());
  }

  if (std::cout.fail()) {
    std::cerr << "Unable to open log file!" << std::endl;
    return;
  }
  time_t t = time(0);   /// current time
  struct tm* now = localtime(&t);
  std::cout << (now->tm_year + 1900) << '-'
            << (now->tm_mon + 1) << '-'
            <<  now->tm_mday << " "
            <<  now->tm_hour << ":"
            <<  now->tm_min << ":"
            <<  now->tm_sec << std::endl;
  if (fIsLogFile) {
    std::cout.rdbuf(originalCoutBuffer);  // back to original stream
  }
}*/
