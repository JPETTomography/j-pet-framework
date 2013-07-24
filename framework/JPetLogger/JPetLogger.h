/** 
 *   @copyright Copyright (c) 2012, Wojciech Krzemien
 *   @file JPetLogger.h
 *   @version 1.0
 *   @author Wojciech Krzemien
 *   @brief Simple logger class. Don't use directly. Macros from JPetLoggerInclude.h should be used instead. 
 *   JPetLogger class implements a simple logging functionality.
 *   For every message the logfile stream is opened, the message is written and the stream is closed again. This assures that no messages are lost in case of errrors.
 */

#ifndef JPETLOGGER_H
#define JPETLOGGER_H

#include <fstream>
#include <iostream>
#include <string>

class JPetLogger {
 public:
  static void dateAndTime();
  inline static void warning(const char* func, const char* msg) {
    logMessage(func, msg, kWarning);
  }
  inline static void error(const char* func, const char* msg) {
    logMessage(func, msg, kError);
  }
  inline static void info(const char* func, const char* msg) {
    logMessage(func, msg, kInfo);
  }

  inline static void warning(const char* func, const std::string& msg) {
    logMessage(func , msg.c_str(), kWarning);
  }
  inline static void error(const char* func, const std::string& msg) {
    logMessage(func, msg.c_str(), kError);
  }
  inline static void info(const char* func, const std::string& msg) {
    logMessage(func, msg.c_str(), kInfo);
  }
 private:
  enum MessageType {kInfo, kWarning, kError};

  JPetLogger();
  JPetLogger(const JPetLogger&);
  JPetLogger& operator=(const JPetLogger&);

  static void logMessage(const char* func, const char* msg, MessageType type);

  static const char* fFileName;
  static bool fIsLogFile;
};

#endif /*  !JPETLOGGER_H */

