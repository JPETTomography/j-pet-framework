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

#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

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

JPetLogger::JPetLogger()
{
  init();
}

void JPetLogger::init()
{
  typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> text_sink;
  boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

  sink->locked_backend()->add_stream(
    boost::make_shared<std::ofstream>(generateFilename()));

  sink->set_formatter(&JPetLogger::formatter);

  boost::log::core::get()->add_sink(sink);
  boost::log::add_common_attributes();
}

void JPetLogger::formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm)
{
  boost::log::value_ref<std::string> fullpath = boost::log::extract<std::string>("File", rec);
  boost::log::value_ref<std::string> fullfunction = boost::log::extract<std::string>("Function", rec);

  strm << boost::log::extract<unsigned int>("LineID", rec) << ": [";
  strm << boost::filesystem::path(fullpath.get()).filename().string() << ":";
  strm << fullfunction << "@";
  strm << boost::log::extract<int>("Line", rec) << "] ";


  // The same for the severity level.
  // The simplified syntax is possible if attribute keywords are used.
  strm << "<" << rec[boost::log::trivial::severity] << "> ";

  // Finally, put the record message to the stream
  strm << rec[boost::log::expressions::smessage];
}
