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
 *  @file JPetLogger.h
 */

#ifndef JPETLOGGER_H
#define JPETLOGGER_H

#include "JPetTMessageHandler.h"
#include "JPetTextFileBackend.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#ifndef __CINT__
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#endif

/**
 * @brief Simple logger class.
 *
 * Logger class for printing out varius statusses in the resulting .log file
 * Don't use directly, rather by including JPetLoggerInclude.h
 * and using macros from there. It is wrapper for Boost.Log
 * that is multithread safe and implements own formatter.
 */

class JPetLogger {
public:
#ifndef __CINT__

  static boost::log::sources::severity_logger<boost::log::trivial::severity_level>& getSeverity()
  {
    static bool isInitialized = false;
    if (!isInitialized) {
      JPetLogger::getInstance(); // if JPetLogger is not initialized, get
                                 // instance to call constructor
      isInitialized = true;
    }
    static boost::log::sources::severity_logger<boost::log::trivial::severity_level> sev;
    static JPetTMessageHandler rootHandler;
    return sev;
  }

  static void formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& out_stream);

  static void setLogLevel(boost::log::trivial::severity_level level) {
    JPetLogger::getInstance().sink->set_filter(boost::log::trivial::severity >= level);
  }

  static JPetLogger& getInstance()
  {
    static JPetLogger logger;
    return logger;
  }

  static void setThreadsEnabled(bool value) { JPetLogger::getInstance().isThreadsEnabled = value; }

  static void setRotationSize(unsigned int value) { JPetLogger::getInstance().backend->set_rotation_size(value); }
#else
  void getSeverity();
  void formatter();
  void setLogLevel();
#endif

private:
  JPetLogger();
  JPetLogger(const JPetLogger&);
  JPetLogger& operator=(const JPetLogger&);

  const int kRotationSize = 10 * 1024 * 1024; // 10 * MiB, log will rotate after 10MiB

#ifndef __CINT__
  void init();
  boost::shared_ptr<JPetTextFileBackend> backend;
  typedef boost::log::sinks::synchronous_sink<JPetTextFileBackend> sink_t;
  boost::shared_ptr<sink_t> sink;

  bool isThreadsEnabled = false;
#endif
};

#endif /* !JPETLOGGER_H */
