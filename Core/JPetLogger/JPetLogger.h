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
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#endif

class JPetLogger
{
public:
#ifndef __CINT__
  static boost::log::sources::severity_logger<boost::log::trivial::severity_level>& getSeverity()
  {
    static boost::log::sources::severity_logger<boost::log::trivial::severity_level> sev;
    return sev;
  }
#else
  static void* getSeverity();
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
  static void formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm);
  static void init();
#endif
};

#endif /*  !JPETLOGGER_H */

