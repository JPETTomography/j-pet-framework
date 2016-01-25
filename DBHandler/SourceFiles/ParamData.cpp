// Param Data - ParamData.cpp (Parameter Data)
#include "../HeaderFiles/ParamData.h"


namespace DB
{

namespace DATA
{

ParamData::ParamData(SERVER::ParamServer &p_paramServer) : m_paramServer(p_paramServer)
{
}

ParamData::~ParamData()
{
}

boost::optional<TOMB_INPUT_MAP_VALUE_TYPE > ParamData::getTOMBInputIdFromTOMBInputMap(TOMB_INPUT_MAP_KEY_TYPE p_TRBIdAndTRBoutputId) const
{
  return m_paramServer.TOMBInput_Map().valueFromMap(p_TRBIdAndTRBoutputId);
}

boost::optional<TOMB_INPUT_MAP_KEY_TYPE > ParamData::getTRBIdAndTRBoutputIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const
{
  if( !m_paramServer.TOMBInput_Map().empty() )
  {
    for(std::map<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >::const_iterator it = m_paramServer.TOMBInput_Map().m_map.begin(); it != m_paramServer.TOMBInput_Map().m_map.end(); ++it)
    {
      if(it->second == p_TOMBInputId)
      {
        return it->first;
      }
    }
  }
  return boost::none;
}

boost::optional<int> ParamData::getTRBIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const
{
  if( !m_paramServer.TOMBInput_Map().empty() )
  {
    for(std::map<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >::const_iterator it = m_paramServer.TOMBInput_Map().m_map.begin(); it != m_paramServer.TOMBInput_Map().m_map.end(); ++it)
    {
      if(it->second == p_TOMBInputId)
      {
        return it->first.first;
      }
    }
  }
  return boost::none;
}

boost::optional<int> ParamData::getTRBOutputIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const
{
  if( !m_paramServer.TOMBInput_Map().empty() )
  {
    for(std::map<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >::const_iterator it = m_paramServer.TOMBInput_Map().m_map.begin(); it != m_paramServer.TOMBInput_Map().m_map.end(); ++it)
    {
      if(it->second == p_TOMBInputId)
      {
        return it->first.second;
      }
    }
  }
  return boost::none;
}

} // namespace DATA

} // namespace DB
