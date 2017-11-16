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

// current settings
// 1 - switched on
#define JPETLOGGER_ON 1
#define JPET_LOGGER_LEVEL_INFO 1
#define JPET_LOGGER_LEVEL_WARNING 1
#define JPET_LOGGER_LEVEL_ERROR 1
#define JPET_LOGGER_LEVEL_DEBUG 0
#define JPET_SCREEN_OUTPUT 0

// don't touch this part
#if JPETLOGGER_ON == 1
#include "../JPetLogger/JPetLogger.h"
#define DATE_AND_TIME()   JPetLogger::dateAndTime()
#if JPET_LOGGER_LEVEL_INFO == 1
#define INFO(X)   JPetLogger::info(__func__, X)
#else
#define INFO(X)
#endif
#if JPET_LOGGER_LEVEL_WARNING == 1
#define WARNING(X) JPetLogger::warning(__func__, X)
#else
#define WARNING(X)
#endif
#if JPET_LOGGER_LEVEL_ERROR == 1
#define ERROR(X)   JPetLogger::error(__func__, X)
#else
#define ERROR(X)
#endif
#if JPET_LOGGER_LEVEL_DEBUG == 1
#define DEBUG(X)   JPetLogger::debug(__func__, X)
#else
#define DEBUG(X)
#endif
#else
#define WARNING(X)
#define ERROR(X)
#define INFO(X)
#define DEBUG(X)
#define DATE_AND_TIME()
#endif

#endif
