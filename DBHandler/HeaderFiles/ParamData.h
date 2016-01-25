// Param Data - ParamData.h (Parameter Data)
#ifndef PARAM_DATA_H
#define PARAM_DATA_H

#include "../HeaderFiles/ParamServer.h"
#include "../HeaderFiles/TOMBInputMap.h"


namespace DB
{

namespace DATA
{

class ParamData
{
protected:
  SERVER::ParamServer &m_paramServer;

public:
  ParamData(DB::SERVER::ParamServer &p_paramServer);
  ParamData(const ParamData &p_paramData) = delete;             // do przemyslenia!
  ParamData& operator=(const ParamData &p_paramData) = delete;  // do przemyslenia!
  ParamData(ParamData &&p_paramData) = delete;                  // do przemyslenia!
  ParamData& operator=(ParamData &&p_paramData) = delete;       // do przemyslenia!
  virtual ~ParamData(void);

  virtual boost::optional<TOMB_INPUT_MAP_VALUE_TYPE > getTOMBInputIdFromTOMBInputMap(TOMB_INPUT_MAP_KEY_TYPE p_TRBIdAndTRBoutputId) const;
  virtual boost::optional<TOMB_INPUT_MAP_KEY_TYPE > getTRBIdAndTRBoutputIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const;
  virtual boost::optional<int> getTRBIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const;
  virtual boost::optional<int> getTRBOutputIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const;
};

} // namespace DATA

} // namespace DB

#endif // PARAM_DATA_H
