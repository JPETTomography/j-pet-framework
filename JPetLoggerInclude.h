/** 
 *   @copyright Copyright (c) 2012, Wojciech Krzemien
 *   @file JPetLoggerInclude.h
 *   @version 1.0
 *   @author Wojciech Krzemien
 *   @brief Configuration file for the Logger class
 *   Three independent level of logging are defined: LEVEL_INFO, LEVEL_WARNING and LEVEL_ERROR
 *   Levels can be switched on/off separately, by assign the value different than 1.
 *   The messages can be redirected to the screen if the SCREEN_OUTPUT is 1.
 *   Also the whole JPetLogger can be switched off/on by setting the JPETLOGGER_ON flag to 1.
 */

// current settings
// 1 - switched on
#define JPETLOGGER_ON 1
#define JPET_LOGGER_LEVEL_INFO 1
#define JPET_LOGGER_LEVEL_WARNING 1
#define JPET_LOGGER_LEVEL_ERROR 1
#define JPET_SCREEN_OUTPUT 0

// don't touch this part
#if JPETLOGGER_ON == 1
  #include "./framework/JPetLogger/JPetLogger.h"
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
#else
  #define WARNING(X)
  #define ERROR(X)
  #define INFO(X)
  #define DATE_AND_TIME()
#endif
