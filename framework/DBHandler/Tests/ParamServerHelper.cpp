// Param Server Helper - ParamServerHelper.cpp (Parameter Server Helper)
#ifndef PARAM_SERVER_HELPER_H
#define PARAM_SERVER_HELPER_H

//#include "../HeaderFiles/ParamServer.h"
//#include "DBHandlerHelper.cpp"
//#include "../HeaderFiles/DBHandler.h"
#include "../HeaderFiles/ParamServer.h"


namespace DB
{

namespace TEST
{

class ParamServerHelper : public SERVER::ParamServer
{
public:
  ParamServerHelper(DB::SERVICES::DBHandler &p_dbHandlerInstance);
  ~ParamServerHelper(void);

  using SERVER::ParamServer::m_photoMultiplierMap;
  using SERVER::ParamServer::m_runDataMap;

  using SERVER::ParamServer::clearPhotoMultiplierMap;
  using SERVER::ParamServer::clearRunDataMap;

  using SERVER::ParamServer::eraseElementFromPhotoMultiplierMap;
  using SERVER::ParamServer::eraseElementFromRunDataMap;
};


ParamServerHelper::ParamServerHelper(DB::SERVICES::DBHandler &p_dbHandlerInstance) : SERVER::ParamServer(p_dbHandlerInstance)
{
}

ParamServerHelper::~ParamServerHelper()
{
}

} // namespace TEST

} // namespace DB

#endif // PARAM_SERVER_HELPER_H
