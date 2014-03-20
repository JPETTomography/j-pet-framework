// Param Server - ParamServer.cpp (Parameter Server)
#include <iostream>
#include <fstream>
#include "../HeaderFiles/ParamServer.h"


namespace DB
{

namespace SERVER
{

ParamServer::ParamServer() :
                            m_dbHandlerInstance(DB::SERVICES::DBHandler::getInstance()),
                            m_fileNameToSavePhotoMultiplierMap("PhotoMultiplierMap.txt")
{
}

ParamServer::ParamServer(DB::SERVICES::DBHandler &p_dbHandlerInstance) :
                                                                        m_dbHandlerInstance(p_dbHandlerInstance),
                                                                        m_fileNameToSavePhotoMultiplierMap("PhotoMultiplierMap.txt")
{

}

ParamServer::~ParamServer()
{
  DB::SERVICES::DBHandler::deleteInstance();  // do przemyslenia!
}

int ParamServer::connectToDatabase()
{
  return m_dbHandlerInstance.connect();
}

int ParamServer::disconnectFromDatabase()
{
  return m_dbHandlerInstance.disconnect();
}

void ParamServer::clearPhotoMultiplierMap()
{
  m_photoMultiplierMap.clear();
}

void ParamServer::clearRunDataMap()
{
  m_runDataMap.clear();
}

void ParamServer::eraseElementFromPhotoMultiplierMap(int p_slotId)
{
  std::map<int, std::pair<int, int > >::iterator l_iter = m_photoMultiplierMap.find(p_slotId);

  if(l_iter != m_photoMultiplierMap.end())
  {
    m_photoMultiplierMap.erase(l_iter);
  }
}

void ParamServer::eraseElementFromRunDataMap(int p_run_id)
{
  std::map<int, DATA::RunData>::iterator l_iter = m_runDataMap.begin();

  if(l_iter != m_runDataMap.end())
  {
    m_runDataMap.erase(l_iter);
  }
}

void ParamServer::fillPhotoMultiplierMap()
{
  //std::string l_sqlQuerry = "SELECT \"Run\".id AS runid, \"Setup\".id AS setupid, \"HVPMConnection\".id AS hvpmconnid, \"HVPMConnection\".isrightside, \"HVPMConnection\".slot_id AS slot_id, \"PhotoMultiplier\".id AS photomid FROM \"Run\" INNER JOIN \"Setup\" ON \"Run\".setup_id = \"Setup\".id INNER JOIN \"HVPMConnection\" ON \"Setup\".id = \"HVPMConnection\".setup_id INNER JOIN \"PhotoMultiplier\" ON \"HVPMConnection\".photomultiplier_id = \"PhotoMultiplier\".id ORDER BY \"HVPMConnection\".slot_id";
  std::string l_sqlQuerry = "SELECT * FROM photomultiplierinformationfunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  //std::cout << "l_runDbResults.size() = " << l_runDbResults.size() << std::endl;

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    int l_loopCounter = 1;
    int l_photoMultiplierIdLeft = -1;

    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      if( ((l_loopCounter % 2) == 0) && (l_loopCounter > 0) )
      {
        /*int l_runid = row["runid"].as<int>();
        int l_setupid = row["setupid"].as<int>();
        int l_hvpmconnid = row["hvpmconnid"].as<int>();
        bool l_isrightside = row["isrightside"].as<bool>();*/
        int l_slotId = row["slot_id"].as<int>();
        int l_photoMultiplierIdRight = row["photomid"].as<int>();

        //std::cout << l_runid << " " << l_setupid << " " << l_hvpmconnid << " " << l_isrightside << " " << l_slotId << " " << l_photoMultiplierIdLeft << " " << l_photoMultiplierIdRight << "\n";
        //std::cout << l_loopCounter << std::endl;
        //std::cout << "l_photoMultiplierIdLeft = " << l_photoMultiplierIdLeft << " l_photoMultiplierIdRight = " << l_photoMultiplierIdRight << std::endl;

        m_photoMultiplierMap.insert(std::pair<int, std::pair<int, int > >(l_slotId, std::make_pair(l_photoMultiplierIdLeft, l_photoMultiplierIdRight)));

        l_loopCounter = 1;
        continue;
      }

      l_photoMultiplierIdLeft = row["photomid"].as<int>();
      ++l_loopCounter;
    }
  }
}

void ParamServer::fillRunDataMap()
{
  std::string l_sqlQuerry = "SELECT * FROM runDataFunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      int l_runId = row["run_id"].as<int>();
      std::string l_runStart = row["runstart"].as<std::string>();
      std::string l_filePath = row["filepath"].as<std::string>();
      std::string l_runDescription = row["rundescription"].as<std::string>();
      std::string l_information = row["information"].as<std::string>();

      DATA::RunData l_runData(l_runStart, l_filePath, l_runDescription, l_information);
      m_runDataMap.insert(std::pair<int, DATA::RunData>(l_runId, l_runData));
    }
  }
}

void ParamServer::showPhotoMultiplierMap() const
{
  for(std::map<int, std::pair<int, int > >::const_iterator it = m_photoMultiplierMap.begin(); it != m_photoMultiplierMap.end(); ++it)
  {
    std::cout << "Key (slot_id) = " << it->first << " photoMultilpierIdLeft = " << it->second.first << " photoMultilpierIdRight = " << it->second.second << std::endl;
  }
}

void ParamServer::showRunDataMap() const
{
  for(std::map<int, DATA::RunData>::const_iterator it = m_runDataMap.begin(); it != m_runDataMap.end(); ++it)
  {
    /*std::string l_runStart = it->second.runStart();
    std::string l_filePath = it->second.filePath();
    std::string l_runDescription = it->second.runDescription();
    std::string l_information = it->second.information();
    std::cout << "Key (run_id) = " << it->first << " runStart = " << l_runStart << " filePath = " << l_filePath << " runDescription = " << l_runDescription << " information = " << l_information << std::endl;*/
    std::cout << "Key (run_id) = " << it->first << " " << it->second << std::endl;
  }
}

boost::optional<std::pair<int, int> > ParamServer::pairOfPhotoMultiplierForSlotId(int p_slotId)
{
  if( !m_photoMultiplierMap.empty() )
  {
    for(std::map<int, std::pair<int, int > >::const_iterator it = m_photoMultiplierMap.begin(); it != m_photoMultiplierMap.end(); ++it)
    {
      if(it->first == p_slotId)
      {
        //std::cout << "TEST = " << m_photoMultiplierMap[p_slotId].first << m_photoMultiplierMap[p_slotId].second << std::endl;
        return std::make_pair(m_photoMultiplierMap[p_slotId].first, m_photoMultiplierMap[p_slotId].second);
      }
    }
  }
  return boost::none;
}

boost::optional<DATA::RunData> ParamServer::dataFromRun(int p_run_id)
{
  if( !m_runDataMap.empty() )
  {
    for(std::map<int, DATA::RunData>::const_iterator it = m_runDataMap.begin(); it != m_runDataMap.end(); ++it)
    {
      if(it->first == p_run_id)
      {
        return m_runDataMap[p_run_id];
      }
    }
  }

  return boost::none;
}

size_t ParamServer::sizeOfPhotoMultiplierMap() const
{
  return m_photoMultiplierMap.size();
}

size_t ParamServer::sizeOfRunDataMap() const
{
  return m_runDataMap.size();
}

void ParamServer::savePhotoMultiplierMapToFile(std::string p_fileName)
{
  m_fileNameToSavePhotoMultiplierMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "SLOT_ID " << "PHOTOMULTIPLIER_LEFT_ID" << " PHOTOMULTIPLIER_RIGHT_ID\n";

  if(l_file.is_open())
  {
    for(std::map<int, std::pair<int, int > >::const_iterator it = m_photoMultiplierMap.begin(); it != m_photoMultiplierMap.end(); ++it)
    {
      l_file << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }
    l_file.close();
  }
  else
  {
    std::cerr << "Unable write to file : " << p_fileName << std::endl;
  }
}

bool ParamServer::removeFileWithPhotoMultiplierMap()
{
  if(remove(m_fileNameToSavePhotoMultiplierMap.c_str()) != 0)
  {
    perror("Error deleting file");
  }
  return 0;
}

}	// namespace SERVER

}	// namespace DB
