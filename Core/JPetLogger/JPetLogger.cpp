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
 *  @file JPetLogger.cpp
 */

#include "./JPetLogger.h"

JPetLogger::JPetLogger() { init(); }

void JPetLogger::init() {
  sink = boost::make_shared<sink_t>(boost::log::keywords::file_name = "JPet_%Y-%m-%d_%H-%M-%S.%N.log", boost::log::keywords::auto_flush = true);
  sink->set_formatter(&JPetLogger::formatter);
  boost::log::core::get()->add_sink(sink);
  boost::log::add_common_attributes();
  boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

void JPetLogger::setLogLevel(boost::log::trivial::severity_level level) { sink->set_filter(boost::log::trivial::severity >= level); }

void JPetLogger::formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& out_stream) {
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

boost::log::sources::severity_logger<boost::log::trivial::severity_level>& JPetLogger::getSeverity() {
  static boost::log::sources::severity_logger<boost::log::trivial::severity_level> sev;
  return sev;
}
