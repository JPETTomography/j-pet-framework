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

void ParamServer::showMap() const
{
  for(std::map<int, std::pair<int, int > >::const_iterator it = m_photoMultiplierMap.begin(); it != m_photoMultiplierMap.end(); ++it)
  {
    std::cout << "Key = " << it->first << " photoMultilpierIdLeft = " << it->second.first << " photoMultilpierIdRight = " << it->second.second << std::endl;
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
        std::cout << "TEST = " << m_photoMultiplierMap[p_slotId].first << m_photoMultiplierMap[p_slotId].second << std::endl;
        return std::make_pair(m_photoMultiplierMap[p_slotId].first, m_photoMultiplierMap[p_slotId].second);
      }
    }
  }
  return boost::none;
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

size_t ParamServer::sizeOfPhotoMultiplierMap() const
{
  return m_photoMultiplierMap.size();
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
