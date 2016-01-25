// Param Server - ParamServer.cpp (Parameter Server) (Facade)
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "../HeaderFiles/ParamServer.h"


namespace DB
{

namespace SERVER
{

ParamServer::ParamServer(int p_run_id) :
                            m_dbHandlerInstance(SERVICES::DBHandler::getInstance()),
                            m_photoMultiplierMap(SERVICES::DBHandler::getInstance()),
                            m_runDataMap(SERVICES::DBHandler::getInstance()),
                            m_TRBThresholdMap(SERVICES::DBHandler::getInstance()),
                            m_PhotoMultiplierIdMap(SERVICES::DBHandler::getInstance()),
                            m_TOMBInputMap(SERVICES::DBHandler::getInstance()),
                            m_passedInformationMap(SERVICES::DBHandler::getInstance())
{
  if(p_run_id != -1)
  {
    m_photoMultiplierMap.fillMap(p_run_id);
    m_runDataMap.fillMap();
    m_TRBThresholdMap.fillMap(p_run_id);
    m_PhotoMultiplierIdMap.fillMap(p_run_id);
    m_TOMBInputMap.fillMap(p_run_id);
    m_passedInformationMap.fillMap(p_run_id);
  }
}

ParamServer::ParamServer(SERVICES::DBHandler &p_dbHandlerInstance) :
                                                                    m_dbHandlerInstance(p_dbHandlerInstance),
                                                                    m_photoMultiplierMap(p_dbHandlerInstance),
                                                                    m_runDataMap(p_dbHandlerInstance),
                                                                    m_TRBThresholdMap(p_dbHandlerInstance),
                                                                    m_PhotoMultiplierIdMap(p_dbHandlerInstance),
                                                                    m_TOMBInputMap(p_dbHandlerInstance),
                                                                    m_passedInformationMap(p_dbHandlerInstance)
{
}

ParamServer::~ParamServer()
{
  SERVICES::DBHandler::deleteInstance();  // do przemyslenia!
}

int ParamServer::connectToDatabase()
{
  return m_dbHandlerInstance.connect();
}

int ParamServer::disconnectFromDatabase()
{
  return m_dbHandlerInstance.disconnect();
}

DATA::PhotoMultiplierMap& ParamServer::photoMultiplier_Map()
{
  return m_photoMultiplierMap;
}

DATA::RunDataMap& ParamServer::runData_Map()
{
  return m_runDataMap;
}

DATA::TRBThresholdMap& ParamServer::TRBThreshold_Map()
{
  return m_TRBThresholdMap;
}

DATA::PhotoMultiplierIdMap& ParamServer::photoMultiplierId_Map()
{
  return m_PhotoMultiplierIdMap;
}

DATA::TOMBInputMap& ParamServer::TOMBInput_Map()
{
  return m_TOMBInputMap;
}

DATA::PassedInformationMap& ParamServer::passedInformation_Map()
{
  return m_passedInformationMap;
}

boost::optional<DATA::RunData> ParamServer::runInformation(int p_run_id)
{
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM runDataFunction(" + l_run_id + ");";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    pqxx::result::const_iterator row = l_runDbResults.begin();

    std::string l_runStart = row["runstart"].as<std::string>();
    std::string l_filePath = row["filepath"].as<std::string>();
    std::string l_runDescription = row["rundescription"].as<std::string>();
    std::string l_information = row["information"].as<std::string>();

    return DATA::RunData(l_runStart, l_filePath, l_runDescription, l_information);
  }

  return boost::none;
}

}	// namespace SERVER

}	// namespace DB
