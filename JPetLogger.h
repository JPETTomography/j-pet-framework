/** 
 *   @copyright Copyright (c) 2012, Wojciech Krzemien
 *   @file EDLogger.h
 *   @version 1.0
 *   @author Wojciech Krzemien
 *   @brief Simple logger class. Don't use directly. Macros from EDLoggerInclude.h should be used instead. 
 *   EDLogger class implements a simple logging functionality.
 *   For every message the logfile stream is opened, the message is written and the stream is closed again. This assures that no messages are lost in case of errrors.
 */

#ifndef EDLOGGER_H
#define EDLOGGER_H

#include <fstream>
#include <iostream>
#include <string>

class EDLogger {
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

  EDLogger();
  EDLogger(const EDLogger&);
  EDLogger& operator=(const EDLogger&);

  static void logMessage(const char* func, const char* msg, MessageType type);

  static const char* fFileName;
  static bool fIsLogFile;
};

#endif /*  !EDLOGGER_H */

