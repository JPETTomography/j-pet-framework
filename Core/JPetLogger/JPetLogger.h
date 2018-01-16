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

#include <ostream>
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
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#endif

class JPetLogger
{
public:

#ifndef __CINT__
  static boost::log::sources::severity_logger<boost::log::trivial::severity_level>& getSeverity()
  {
    static bool isInitialized = false;
    if (!isInitialized) {
      init();
      isInitialized = true;
    }
    static boost::log::sources::severity_logger<boost::log::trivial::severity_level> sev;
    return sev;
  }

  static void formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm)
  {
    boost::log::value_ref<std::string> fullpath = boost::log::extract<std::string>("File", rec);
    boost::log::value_ref<std::string> fullfunction = boost::log::extract<std::string>("Function", rec);

    strm << boost::log::extract<unsigned int>("LineID", rec) << ": [";
    strm << boost::filesystem::path(fullpath.get()).filename().string() << ":";
    strm << fullfunction << "@";
    strm << boost::log::extract<int>("Line", rec) << "] ";

    strm << "ThreadID: " << boost::log::extract<int>("ThreadID", rec) << " ";

    // The same for the severity level.
    // The simplified syntax is possible if attribute keywords are used.
    strm << "<" << rec[boost::log::trivial::severity] << "> ";

    // Finally, put the record message to the stream
    strm << rec[boost::log::expressions::smessage];
  }
#else
  static void getSeverity();
  static void formatter();
#endif
  //static void dateAndTime(); -- to reimplement
private:
  JPetLogger();
  JPetLogger(const JPetLogger&);
  JPetLogger& operator=(const JPetLogger&);

#ifndef __CINT__
  inline static const std::string generateFilename()
  {
    return std::string("JPet_") + to_string(boost::uuids::random_generator()()) + std::string(".log");
  }

  static void init()
  {
    typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    sink->locked_backend()->add_stream(
      boost::make_shared<std::ofstream>(generateFilename()));

    sink->set_formatter(&JPetLogger::formatter);

    boost::log::core::get()->add_sink(sink);
    boost::log::add_common_attributes();
  }
#endif
};

#endif /*  !JPETLOGGER_H */

