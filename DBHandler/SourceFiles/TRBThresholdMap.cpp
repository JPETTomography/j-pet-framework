// Threshold TRB Map - ThresholdTRBMap.cpp
#include "../HeaderFiles/TRBThresholdMap.h"
#include <boost/lexical_cast.hpp>


namespace DB
{

namespace DATA
{

TRBThresholdMap::TRBThresholdMap(SERVICES::DBHandler &l_dBHandler) : SerializableMap<TRB_THRESHOLD_MAP_KEY_TYPE, TRB_THRESHOLD_MAP_VALUE_TYPE >("TRBThresholdMap.txt", l_dBHandler)
{
}

TRBThresholdMap::~TRBThresholdMap()
{
}

void TRBThresholdMap::fillMap(int p_run_id)
{
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM thresholdFromTRBConfigEntryBasedOnTOMBInputIdFunction(" + l_run_id + ");";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      TRB_THRESHOLD_MAP_KEY_TYPE l_tombinput_id = row["tombinput_id"].as<TRB_THRESHOLD_MAP_KEY_TYPE >();
      TRB_THRESHOLD_MAP_VALUE_TYPE l_trbconfigentry_threshold = row["trbconfigentry_threshold"].as<TRB_THRESHOLD_MAP_VALUE_TYPE >();

      m_map.insert(std::pair<TRB_THRESHOLD_MAP_KEY_TYPE, TRB_THRESHOLD_MAP_VALUE_TYPE >(l_tombinput_id, l_trbconfigentry_threshold));
    }
  }
}

void TRBThresholdMap::showMap() const
{
  for(std::map<TRB_THRESHOLD_MAP_KEY_TYPE, TRB_THRESHOLD_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
  {
    std::cout << "Key (tombinput_id) = " << it->first << " " << it->second << std::endl;
  }
}

boost::optional<TRB_THRESHOLD_MAP_VALUE_TYPE > TRBThresholdMap::valueFromMap(TRB_THRESHOLD_MAP_KEY_TYPE p_key)
{
  if( !m_map.empty() )
  {
    for(std::map<TRB_THRESHOLD_MAP_KEY_TYPE, TRB_THRESHOLD_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      if(it->first == p_key)
      {
        return m_map[p_key];
      }
    }
  }

  return boost::none;
}

void TRBThresholdMap::saveMapToFile(std::string p_fileName)
{
  m_fileNameToSaveMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "TOMB_INPUT_ID" << " TRB_CONFIG_ENTRY_THRESHOLD" << "\n";

  if(l_file.is_open())
  {
    for(std::map<TRB_THRESHOLD_MAP_KEY_TYPE, TRB_THRESHOLD_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
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
