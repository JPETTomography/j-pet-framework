// PhotoMultiplier Map - PhotoMultiplierMap.h
#include "../HeaderFiles/PhotoMultiplierMap.h"
#include <boost/lexical_cast.hpp>


namespace DB
{

namespace DATA
{

PhotoMultiplierMap::PhotoMultiplierMap(SERVICES::DBHandler &l_dBHandler) : SerializableMap<PHOTOMULTIPLIER_MAP_KEY_TYPE, PHOTOMULTIPLIER_MAP_VALUE_TYPE >("PhotoMultiplierMap.txt", l_dBHandler)
{
}

PhotoMultiplierMap::~PhotoMultiplierMap()
{
}

void PhotoMultiplierMap::fillMap(int p_run_id)
{
  //std::string l_sqlQuerry = "SELECT \"Run\".id AS runid, \"Setup\".id AS setupid, \"HVPMConnection\".id AS hvpmconnid, \"HVPMConnection\".isrightside, \"HVPMConnection\".slot_id AS slot_id, \"PhotoMultiplier\".id AS photomid FROM \"Run\" INNER JOIN \"Setup\" ON \"Run\".setup_id = \"Setup\".id INNER JOIN \"HVPMConnection\" ON \"Setup\".id = \"HVPMConnection\".setup_id INNER JOIN \"PhotoMultiplier\" ON \"HVPMConnection\".photomultiplier_id = \"PhotoMultiplier\".id ORDER BY \"HVPMConnection\".slot_id";
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM photomultiplierinformationfunction(" + l_run_id + ");";
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
        int l_slotId = row["slot_id"].as<PHOTOMULTIPLIER_MAP_KEY_TYPE >();
        int l_photoMultiplierIdRight = row["photomid"].as<int>();

        //std::cout << l_runid << " " << l_setupid << " " << l_hvpmconnid << " " << l_isrightside << " " << l_slotId << " " << l_photoMultiplierIdLeft << " " << l_photoMultiplierIdRight << "\n";
        //std::cout << l_loopCounter << std::endl;
        //std::cout << "l_photoMultiplierIdLeft = " << l_photoMultiplierIdLeft << " l_photoMultiplierIdRight = " << l_photoMultiplierIdRight << std::endl;

        m_map.insert(std::pair<PHOTOMULTIPLIER_MAP_KEY_TYPE, PHOTOMULTIPLIER_MAP_VALUE_TYPE >(l_slotId, std::make_pair(l_photoMultiplierIdLeft, l_photoMultiplierIdRight)));

        l_loopCounter = 1;
        continue;
      }

      l_photoMultiplierIdLeft = row["photomid"].as<int>();
      ++l_loopCounter;
    }
  }
}

void PhotoMultiplierMap::showMap() const
{
  for(std::map<PHOTOMULTIPLIER_MAP_KEY_TYPE, PHOTOMULTIPLIER_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
  {
    std::cout << "Key (slot_id) = " << it->first << " photoMultilpierIdLeft = " << it->second.first << " photoMultilpierIdRight = " << it->second.second << std::endl;
  }
}

boost::optional<PHOTOMULTIPLIER_MAP_VALUE_TYPE > PhotoMultiplierMap::valueFromMap(PHOTOMULTIPLIER_MAP_KEY_TYPE p_key)
{
  if( !m_map.empty() )
  {
    for(std::map<PHOTOMULTIPLIER_MAP_KEY_TYPE, PHOTOMULTIPLIER_MAP_VALUE_TYPE >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
      if(it->first == p_key)
      {
        //std::cout << "TEST = " << m_photoMultiplierMap[p_slotId].first << m_photoMultiplierMap[p_slotId].second << std::endl;
        return std::make_pair(m_map[p_key].first, m_map[p_key].second);
      }
    }
  }
  return boost::none;
}

void PhotoMultiplierMap::saveMapToFile(std::string p_fileName)
{
  m_fileNameToSaveMap = p_fileName;

  std::ofstream l_file;
  l_file.open(p_fileName.c_str());
  l_file << "SLOT_ID " << " PHOTOMULTIPLIER_LEFT_ID" << " PHOTOMULTIPLIER_RIGHT_ID\n";

  if(l_file.is_open())
  {
    for(std::map<PHOTOMULTIPLIER_MAP_KEY_TYPE, std::pair<int, int > >::const_iterator it = m_map.begin(); it != m_map.end(); ++it)
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

} // namespace DATA

} // namespace DB
