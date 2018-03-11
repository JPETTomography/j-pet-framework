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
 *  Four independent level of logging are defined: INFO, WARNING, ERROR and DEBUG.
 *  Also general macro is defined that allows to create user own level of logging.
 */
#ifndef JPETLOGGER_INCLUDE_H
#define JPETLOGGER_INCLUDE_H

#include "./JPetLogger/JPetLogger.h"

#ifndef __CINT__
#include <boost/log/utility/manipulators/add_value.hpp> //for add_value
#include <boost/log/attributes/scoped_attribute.hpp>    //for BOOST_LOG_SCOPED_THREAD_TAG
#endif

#define CUSTOM_LOG(logger, sev, X) BOOST_LOG_SEV(logger, sev) << boost::log::add_value("Line", __LINE__) << boost::log::add_value("File", __FILE__) << boost::log::add_value("Function", __func__) << X;

#define INFO(X) CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::info, X)
#define WARNING(X) CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::warning, X)
#define ERROR(X)   CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::error, X)
#define DEBUG(X)   CUSTOM_LOG(JPetLogger::getSeverity(), boost::log::trivial::debug, X)

#define LOG(X, sev) CUSTOM_LOG(JPetLogger::getSevarity(), sev, X)

#endif
