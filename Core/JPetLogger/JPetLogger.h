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

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#ifndef __CINT__
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

  boost::log::sources::severity_logger<boost::log::trivial::severity_level>& getSeverity();

  static void formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& out_stream);

  void setLogLevel(boost::log::trivial::severity_level level);

  static JPetLogger& getInstance() {
    static JPetLogger logger;
    return logger;
  }
#else
  void getSeverity();
  void formatter();
  void setLogLevel();
#endif

private:
  JPetLogger();
  JPetLogger(const JPetLogger&);
  JPetLogger& operator=(const JPetLogger&);

#ifndef __CINT__

  typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> sink_t;
  boost::shared_ptr<sink_t> sink;

  void init();
#endif
};

#endif /* !JPETLOGGER_H */
