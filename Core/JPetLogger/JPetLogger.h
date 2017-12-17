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
 *  @file JPetLogger.h
 *  @brief Simple logger class. Don't use directly. Macros from JPetLoggerInclude.h should be used instead.
 *  JPetLogger class implements a simple logging functionality.
 *  For every message the logfile stream is opened, the message is written and the stream is closed again. This assures that no messages are lost in case of errrors.
 */

#ifndef JPETLOGGER_H
#define JPETLOGGER_H

#include <fstream>
#include <iostream>
#include <string>

#ifndef __CINT__
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
#endif

class JPetLogger
{
public:
  void init()
  {
    logging::add_file_log(
      keywords::file_name = generateFilename(),
      keywords::format = "[%TimeStamp%]: %Message%");

    logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info);
  }
  static void dateAndTime();
  inline static void warning(const char* func, const char* msg)
  {
    logMessage(func, msg, kWarning);
  }
  inline static void error(const char* func, const char* msg)
  {
    logMessage(func, msg, kError);
  }
  inline static void info(const char* func, const char* msg)
  {
    logMessage(func, msg, kInfo);
  }
  inline static void debug(const char* func, const char* msg)
  {
    logMessage(func, msg, kDebug);
  }

  inline static void warning(const char* func, const std::string& msg)
  {
    logMessage(func , msg.c_str(), kWarning);
  }
  inline static void error(const char* func, const std::string& msg)
  {
    logMessage(func, msg.c_str(), kError);
  }
  inline static void info(const char* func, const std::string& msg)
  {
    logMessage(func, msg.c_str(), kInfo);
  }
  inline static void debug(const char* func, const std::string& msg)
  {
    logMessage(func, msg.c_str(), kDebug);
  }
private:
  enum MessageType {kInfo, kWarning, kError, kDebug};

  JPetLogger();
  JPetLogger(const JPetLogger&);
  JPetLogger& operator=(const JPetLogger&);

#ifndef __CINT__
  inline static const std::string generateFilename()
  {
    return std::string("JPet_") + to_string(boost::uuids::random_generator()()) + std::string(".log");
  }
#endif

  static void logMessage(const char* func, const char* msg, MessageType type);

  static const std::string fFileName;
  static bool fIsLogFile;
};

#endif /*  !JPETLOGGER_H */

