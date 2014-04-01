// TOMB Input Map - TOMBInputMap.h
#include "../HeaderFiles/TOMBInputMap.h"
#include <boost/lexical_cast.hpp>


namespace DB
{

namespace DATA
{

TOMBInputMap::TOMBInputMap(SERVICES::DBHandler &l_dBHandler) : SerializableMap<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >("TOMBInputMap.txt", l_dBHandler)
{
}

TOMBInputMap::~TOMBInputMap()
{
}

void TOMBInputMap::fillMap(int p_run_id)
{
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM tombinputIdBasedOnTRBIdAndTRBoutputIdFunction(" + l_run_id + ");";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      TOMB_INPUT_MAP_KEY_TYPE l_trb_id_trboutput_id = std::make_pair(row["trb_id"].as<int>(), row["trboutput_id"].as<int>());
      TOMB_INPUT_MAP_VALUE_TYPE l_tombinput_id = row["tombinput_id"].as<TOMB_INPUT_MAP_VALUE_TYPE >();

      m_map.insert(std::pair<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >(l_trb_id_trboutput_id, l_tombinput_id));
    }
  }
}

void TOMBInputMap::showMap() const
{
  for(std::map<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
  {
    std::cout << "Key (trb_id_trboutput_id) = " << it->first.first << " " << it->first.second << " " << it->second << std::endl;
  }
}

boost::optional<TOMB_INPUT_MAP_VALUE_TYPE > TOMBInputMap::valueFromMap(TOMB_INPUT_MAP_KEY_TYPE p_key)
{
  if( !m_map.empty() )
  {
    for(std::map<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      if(it->first == p_key)
      {
        return m_map[p_key];
      }
    }
  }

  return boost::none;
}

void TOMBInputMap::saveMapToFile(std::string p_fileName)
{
  m_fileNameToSaveMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "TRB_ID" << " TRBOUTPUT_ID" << " TOMBINPUT_ID" << "\n";

  if(l_file.is_open())
  {
    for(std::map<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      l_file << it->first.first << " " << it->first.second << " " << it->second << "\n";
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
