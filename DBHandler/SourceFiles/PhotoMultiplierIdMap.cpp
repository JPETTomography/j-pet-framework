// PhotoMultiplier Id Map - PhotoMultiplierIdMap.cpp
#include "../HeaderFiles/PhotoMultiplierIdMap.h"
#include <boost/lexical_cast.hpp>


namespace DB
{

namespace DATA
{

PhotoMultiplierIdMap::PhotoMultiplierIdMap(SERVICES::DBHandler &l_dBHandler) : SerializableMap<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >("PhotoMultiplierIdMap.txt", l_dBHandler)
{
}

PhotoMultiplierIdMap::~PhotoMultiplierIdMap()
{
}

void PhotoMultiplierIdMap::fillMap(int p_run_id)
{
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM photomultiplierIdBasedOnTOMBInputIdFunction(" + l_run_id + ");";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      int l_tombinput_id = row["tombinput_id"].as<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE >();
      int l_photomultiplier_id = row["photomultiplier_id"].as<PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >();

      m_map.insert(std::pair<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >(l_tombinput_id, l_photomultiplier_id));
    }
  }
}

void PhotoMultiplierIdMap::showMap() const
{
  for(std::map<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
  {
    std::cout << "Key (tombinput_id) = " << it->first << " " << it->second << std::endl;
  }
}

boost::optional<PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE > PhotoMultiplierIdMap::valueFromMap(PHOTOMULTIPLIER_ID_MAP_KEY_TYPE p_key)
{
  if( !m_map.empty() )
  {
    for(std::map<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      if(it->first == p_key)
      {
        return m_map[p_key];
      }
    }
  }

  return boost::none;
}

void PhotoMultiplierIdMap::saveMapToFile(std::string p_fileName)
{
  m_fileNameToSaveMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "TOMB_INPUT_ID" << " PHOTOMULTIPLIER_ID" << "\n";

  if(l_file.is_open())
  {
    for(std::map<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
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
