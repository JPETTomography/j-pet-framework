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
 *  @file JPetLoggerInclude.h
 *  @brief Configuration file for the Logger class
 *  Three independent level of logging are defined: LEVEL_INFO, LEVEL_WARNING and LEVEL_ERROR
 *  Levels can be switched on/off separately, by assign the value different than 1.
 *  The messages can be redirected to the screen if the SCREEN_OUTPUT is 1.
 *  Also the whole JPetLogger can be switched off/on by setting the JPETLOGGER_ON flag to 1.
 */
#ifndef JPETLOGGER_INCLUDE_H
#define JPETLOGGER_INCLUDE_H

#include "./JPetLogger/JPetLogger.h"

#ifndef __CINT__
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/filesystem.hpp>

#endif

#define CUSTOM_LOG(logger, sev) BOOST_LOG_SEV(logger, sev)                                       \
                                    << boost::log::add_value("Line", __LINE__)                   \
                                    << boost::log::add_value("File", __FILE__)                   \
                                    << boost::log::add_value("Function", BOOST_CURRENT_FUNCTION)

#define DATE_AND_TIME()   JPetLogger::dateAndTime()
#define INFO(X) CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::info) << X
#define WARNING(X) CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::warning) << X
#define ERROR(X)   CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::error) << X
#define DEBUG(X)   CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::debug) << X

#endif
