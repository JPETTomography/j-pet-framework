// Passed Information Map - PassedInformationMap.cpp
#include "../HeaderFiles/PassedInformationMap.h"
#include <boost/lexical_cast.hpp>


namespace DB
{

namespace DATA
{

PassedInformationMap::PassedInformationMap(SERVICES::DBHandler &l_dBHandler) : SerializableMap<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >("PassedInformationMap.txt", l_dBHandler)
{

}

PassedInformationMap::~PassedInformationMap()
{

}

void PassedInformationMap::fillMap(int p_run_id)
{
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM passedInformationIsTimeBasedOnTOMBInputIdFunction(" + l_run_id + ");";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      PASSED_INFORMATION_MAP_KEY_TYPE l_tombinput_id = row["tombinput_id"].as<PASSED_INFORMATION_MAP_KEY_TYPE >();
      PASSED_INFORMATION_MAP_VALUE_TYPE l_konradBoardOutput_passedinformationistime = row["konradBoardOutput_passedinformationistime"].as<PASSED_INFORMATION_MAP_VALUE_TYPE>();

      m_map.insert(std::pair<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >(l_tombinput_id, l_konradBoardOutput_passedinformationistime));
    }
  }
}

void PassedInformationMap::showMap() const
{
  for(std::map<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
  {
    std::cout << "Key (tombinput_id) = " << it->first << " " << it->second << std::endl;
  }
}

boost::optional<PASSED_INFORMATION_MAP_VALUE_TYPE > PassedInformationMap::valueFromMap(PASSED_INFORMATION_MAP_KEY_TYPE p_key)
{
  if( !m_map.empty() )
  {
    for(std::map<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      if(it->first == p_key)
      {
        return m_map[p_key];
      }
    }
  }

  return boost::none;
}

void PassedInformationMap::saveMapToFile(std::string p_fileName)
{
  m_fileNameToSaveMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "TOMB_INPUT_ID" << " PASSED_INFORMATION_IS_TIME" << "\n";

  if(l_file.is_open())
  {
    for(std::map<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      l_file << it->first << " " << it->second << "\n";
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
