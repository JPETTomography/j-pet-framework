// Run Data Map - RunDataMap.cpp
#include "../HeaderFiles/RunDataMap.h"
#include <boost/lexical_cast.hpp>


namespace DB
{

namespace DATA
{

RunDataMap::RunDataMap(SERVICES::DBHandler &l_dBHandler) : SerializableMap<RUN_DATA_MAP_KEY_TYPE, RUN_DATA_MAP_VALUE_TYPE >("RunDataMap.txt", l_dBHandler)
{
}

RunDataMap::~RunDataMap()
{
}

void RunDataMap::fillMap()
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
      m_map.insert(std::pair<RUN_DATA_MAP_KEY_TYPE, RUN_DATA_MAP_VALUE_TYPE >(l_runId, l_runData));
    }
  }
}

void RunDataMap::showMap() const
{
  for(std::map<RUN_DATA_MAP_KEY_TYPE, RUN_DATA_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
  {
    /*std::string l_runStart = it->second.runStart();
    std::string l_filePath = it->second.filePath();
    std::string l_runDescription = it->second.runDescription();
    std::string l_information = it->second.information();
    std::cout << "Key (run_id) = " << it->first << " runStart = " << l_runStart << " filePath = " << l_filePath << " runDescription = " << l_runDescription << " information = " << l_information << std::endl;*/
    std::cout << "Key (run_id) = " << it->first << " " << it->second << std::endl;
  }
}

boost::optional<RUN_DATA_MAP_VALUE_TYPE > RunDataMap::valueFromMap(RUN_DATA_MAP_KEY_TYPE p_key)
{
  if( !m_map.empty() )
  {
    for(std::map<RUN_DATA_MAP_KEY_TYPE, RUN_DATA_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      if(it->first == p_key)
      {
        return m_map[p_key];
      }
    }
  }

  return boost::none;
}

void RunDataMap::saveMapToFile(std::string p_fileName)
{
  m_fileNameToSaveMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "RUN_ID" << " START" << " FILEPATH" << " DESCRIPTION" << " INFORMATION" << "\n";

  if(l_file.is_open())
  {
    for(std::map<RUN_DATA_MAP_KEY_TYPE, RUN_DATA_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      l_file << it->first << " " << it->second<< "\n";
    }
    l_file.close();
  }
  else
  {
    std::cerr << "Unable write to file : " << p_fileName << std::endl;
  }
}

} // namespace DATA

} // namespace DB
