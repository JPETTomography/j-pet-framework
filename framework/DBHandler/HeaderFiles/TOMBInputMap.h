// TOMB Input Map - TOMBInputMap.h
#ifndef TOMB_INPUT_MAP_H
#define TOMB_INPUT_MAP_H

#include <utility>
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef std::pair<int, int> TOMB_INPUT_MAP_KEY_TYPE;
typedef int TOMB_INPUT_MAP_VALUE_TYPE;

class TOMBInputMap : public SerializableMap<TOMB_INPUT_MAP_KEY_TYPE, TOMB_INPUT_MAP_VALUE_TYPE >
{
public:
  TOMBInputMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~TOMBInputMap(void);

  virtual void fillMap(int p_run_id);
  virtual void showMap(void) const;
  virtual boost::optional<TOMB_INPUT_MAP_VALUE_TYPE > valueFromMap(TOMB_INPUT_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);

  friend class ParamData;
};

} // namespace DATA

} // namespace DB

#endif // TOMB_INPUT_MAP_H
