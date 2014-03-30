// Database Handler Helper - DBHandlerHelper.cpp
#ifndef DBHANDLERHELPER_H
#define DBHANDLERHELPER_H

#include "../HeaderFiles/DBHandler.h"


namespace DB
{

namespace TEST
{

class DBHandlerHelper : public SERVICES::DBHandler
{
public:
  using SERVICES::DBHandler::getInstanceForTestsDemand; // UWAGA
};

} // namespace TEST

} // namespace DB

#endif // DBHANDLERHELPER_H
