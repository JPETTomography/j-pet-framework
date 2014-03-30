// PhotoMultiplier Map - PhotoMultiplierMap.h
#ifndef PHOTOMULTIPLIER_MAP_H
#define PHOTOMULTIPLIER_MAP_H

#include <utility>
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef int PHOTOMULTIPLIER_MAP_KEY_TYPE;
typedef std::pair<int, int > PHOTOMULTIPLIER_MAP_VALUE_TYPE;

class PhotoMultiplierMap : public SerializableMap<PHOTOMULTIPLIER_MAP_KEY_TYPE, PHOTOMULTIPLIER_MAP_VALUE_TYPE >
{
public:
  PhotoMultiplierMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~PhotoMultiplierMap(void);

  virtual void fillMap(int p_run_id);
  virtual void showMap(void) const;
  virtual boost::optional<PHOTOMULTIPLIER_MAP_VALUE_TYPE > valueFromMap(PHOTOMULTIPLIER_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);
};

} // namespace DATA

} // namespace DB

#endif // PHOTOMULTIPLIER_MAP_H
