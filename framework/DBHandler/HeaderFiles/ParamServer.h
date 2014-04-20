// Param Server - ParamServer.h (Parameter Server) (Facade)
#ifndef PARAM_SERVER_H
#define PARAM_SERVER_H

#include <map>
#include <utility>
#include <string>
#include <boost/optional.hpp>
//#include "../HeaderFiles/Declarations.h"
#include "../HeaderFiles/DBHandler.h"
#include "../HeaderFiles/RunData.h"
#include "../HeaderFiles/PhotoMultiplierMap.h"
#include "../HeaderFiles/RunDataMap.h"
#include "../HeaderFiles/TRBThresholdMap.h"
#include "../HeaderFiles/PhotoMultiplierIdMap.h"
#include "../HeaderFiles/TOMBInputMap.h"
#include "../HeaderFiles/PassedInformationMap.h"


namespace DB
{

namespace SERVER
{

class ParamServer
{
public:
  ParamServer(int p_run_id = -1);
  ParamServer(SERVICES::DBHandler &p_dbHandlerInstance);  // for the purposes of a test
  ParamServer(const ParamServer &p_paramServer) = delete;             // do przemyslenia!
  ParamServer& operator=(const ParamServer &p_paramServer) = delete;  // do przemyslenia!
  ParamServer(ParamServer &&p_paramServer) = delete;                  // do przemyslenia!
  ParamServer& operator=(ParamServer &&p_paramServer) = delete;       // do przemyslenia!
  virtual ~ParamServer(void);

protected:
  SERVICES::DBHandler &m_dbHandlerInstance;

  DATA::PhotoMultiplierMap m_photoMultiplierMap;
  DATA::RunDataMap m_runDataMap;
  DATA::TRBThresholdMap m_TRBThresholdMap;
  DATA::PhotoMultiplierIdMap m_PhotoMultiplierIdMap;
  DATA::TOMBInputMap m_TOMBInputMap;
  DATA::PassedInformationMap m_passedInformationMap;

  int connectToDatabase(void);
  int disconnectFromDatabase(void);

public:
  virtual DATA::PhotoMultiplierMap& photoMultiplier_Map(void);
  virtual DATA::RunDataMap& runData_Map(void);
  virtual DATA::TRBThresholdMap& TRBThreshold_Map(void);
  virtual DATA::PhotoMultiplierIdMap& photoMultiplierId_Map(void);
  virtual DATA::TOMBInputMap& TOMBInput_Map(void);
  virtual DATA::PassedInformationMap& passedInformation_Map(void);

  virtual boost::optional<DATA::RunData> runInformation(int p_run_id);
};

} // namespace SERVER

} // namespace DB

#endif // PARAM_SERVER_H
