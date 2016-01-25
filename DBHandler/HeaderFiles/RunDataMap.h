// Run Data Map - RunDataMap.h
#ifndef RUN_DATA_MAP_H
#define RUN_DATA_MAP_H

#include <utility>
#include "../HeaderFiles/RunData.h"
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef int           RUN_DATA_MAP_KEY_TYPE;
typedef DATA::RunData RUN_DATA_MAP_VALUE_TYPE;

class RunDataMap : public SerializableMap<RUN_DATA_MAP_KEY_TYPE, RUN_DATA_MAP_VALUE_TYPE >
{
public:
  RunDataMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~RunDataMap(void);

  virtual void fillMap(void);
  virtual void showMap(void) const;
  virtual boost::optional<RUN_DATA_MAP_VALUE_TYPE > valueFromMap(RUN_DATA_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);
};

} // namespace DATA

} // namespace DB

#endif // RUN_DATA_MAP_H
