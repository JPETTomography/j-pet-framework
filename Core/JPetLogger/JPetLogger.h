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
 *  @brief Simple logger class. Don't use directly. Macros from ../JPetLoggerInclude.h should be used instead.
 *  JPetLogger class implements a simple logging functionality.
 *  It is wrapper for Boost.Log that is multithread safe and implements own formatter.
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

#include <boost/log/core.hpp>                               //main logger, get(), add_sink()
#include <boost/log/trivial.hpp>                            //for severity_level
#include <boost/log/sinks/text_ostream_backend.hpp>         //for text_ostream_backend sink
#include <boost/log/utility/setup/file.hpp>                 //for value_ref
#include <boost/log/utility/setup/common_attributes.hpp>    //for add_common_atributes()
#endif

class JPetLogger
{
public:

#ifndef __CINT__
  inline static boost::log::sources::severity_logger<boost::log::trivial::severity_level>& getSeverity()
  {
    static bool isInitialized = false;
    if (!isInitialized) {
      init();
      setLogLevel(boost::log::trivial::info);
      isInitialized = true;
    }
    static boost::log::sources::severity_logger<boost::log::trivial::severity_level> sev;
    return sev;
  }

  inline static void formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& out_stream)
  {
    boost::log::value_ref<std::string> fullpath = boost::log::extract<std::string>("File", rec);
    boost::log::value_ref<std::string> fullfunction = boost::log::extract<std::string>("Function", rec);

    out_stream << boost::log::extract<unsigned int>("LineID", rec) << ": [";
    out_stream << boost::filesystem::path(fullpath.get()).filename().string() << ":";
    out_stream << fullfunction << "@";
    out_stream << boost::log::extract<int>("Line", rec) << "] ";

    out_stream << "ThreadID: " << boost::log::extract<boost::log::attributes::current_thread_id::value_type>("ThreadID", rec) << " ";

    out_stream << "<" << rec[boost::log::trivial::severity] << "> ";

    out_stream << rec[boost::log::expressions::smessage];
  }

  inline static void setLogLevel(boost::log::trivial::severity_level level)
  {
    boost::log::core::get()->set_filter (
      boost::log::trivial::severity >= level
    );
  }
#else
  static void getSeverity();
  static void formatter();
  static void setLogLevel();
#endif

private:
  JPetLogger();
  JPetLogger(const JPetLogger&);
  JPetLogger& operator=(const JPetLogger&);

#ifndef __CINT__
  inline static const std::string generateFilename()
  {
    return std::string("JPet_") + to_string(boost::uuids::random_generator()()) + std::string(".log");
  }

  inline static void init()
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

