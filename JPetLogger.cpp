/** 
 *   @copyright Copyright (c) 2012, Wojciech Krzemien
 *   @file EDLogger.cc
 *   @version 1.0
 *   @author Wojciech Krzemien
 */

#include <ctime>
#include <cassert>
#include "./JPetLogger.h"
#include "./JPetLoggerInclude.h"

#if ED_SCREEN_OUTPUT == 1
bool EDLogger::fIsLogFile = false;
#else
bool EDLogger::fIsLogFile = true;
#endif
const char* EDLogger::fFileName = "Display.log";


void EDLogger::dateAndTime() {
  std::ofstream log(fFileName, std::ios_base::app);
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
  struct tm * now = localtime(&t);
  std::cout << (now->tm_year + 1900) << '-'
  << (now->tm_mon + 1) << '-'
  <<  now->tm_mday << " "
  <<  now->tm_hour << ":"
  <<  now->tm_min << ":"
  <<  now->tm_sec << std::endl;
  if (fIsLogFile) {
    std::cout.rdbuf(originalCoutBuffer);  // back to original stream
  }
}


void EDLogger::logMessage(const char* func, const char* msg, MessageType type) {
  std::ofstream log(fFileName, std::ios_base::app);
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
  switch (type) {
    case kInfo:
      std::cout << "Info ";
      break;
    case kWarning:
      std::cout << "Warning ";
      break;
    case kError:
      std::cout << "Error ";
      break;
  }
  std::cout << func << "():"
  << msg
  << std::endl;
  if (fIsLogFile) {
    std::cout.rdbuf(originalCoutBuffer);  // back to original stream
  }
}
