// TRB Threshold Map - TRBThresholdMap.h
#ifndef TRB_THRESHOLD_MAP_H
#define TRB_THRESHOLD_MAP_H

#include <utility>
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef int TRB_THRESHOLD_MAP_KEY_TYPE;
typedef float TRB_THRESHOLD_MAP_VALUE_TYPE;

class TRBThresholdMap : public SerializableMap<TRB_THRESHOLD_MAP_KEY_TYPE, TRB_THRESHOLD_MAP_VALUE_TYPE >
{
public:
  TRBThresholdMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~TRBThresholdMap(void);

  virtual void fillMap(int p_run_id);
  virtual void showMap(void) const;
  virtual boost::optional<TRB_THRESHOLD_MAP_VALUE_TYPE > valueFromMap(TRB_THRESHOLD_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);
};

} // namespace DATA

} // namespace DB

#endif // TRB_THRESHOLD_MAP_H
