// PhotoMultiplier Id Map - PhotoMultiplierIdMap.h
#ifndef PHOTOMULTIPLIER_ID_MAP_H
#define PHOTOMULTIPLIER_ID_MAP_H

#include <utility>
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef int PHOTOMULTIPLIER_ID_MAP_KEY_TYPE;
typedef int PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE;

class PhotoMultiplierIdMap : public SerializableMap<PHOTOMULTIPLIER_ID_MAP_KEY_TYPE, PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE >
{
public:
  PhotoMultiplierIdMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~PhotoMultiplierIdMap(void);

  virtual void fillMap(int p_run_id);
  virtual void showMap(void) const;
  virtual boost::optional<PHOTOMULTIPLIER_ID_MAP_VALUE_TYPE > valueFromMap(PHOTOMULTIPLIER_ID_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);
};

} // namespace DATA

} // namespace DB

#endif // PHOTOMULTIPLIER_ID_MAP_H
