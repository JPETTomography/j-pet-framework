// Passed Information Map - PassedInformationMap.h
#ifndef PASSED_INFORMATION_MAP_H
#define PASSED_INFORMATION_MAP_H

#include <utility>
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef int PASSED_INFORMATION_MAP_KEY_TYPE;
typedef bool PASSED_INFORMATION_MAP_VALUE_TYPE;

class PassedInformationMap : public SerializableMap<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >
{
public:
  PassedInformationMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~PassedInformationMap(void);

  virtual void fillMap(int p_run_id);
  virtual void showMap(void) const;
  virtual boost::optional<PASSED_INFORMATION_MAP_VALUE_TYPE > valueFromMap(PASSED_INFORMATION_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);
};

} // namespace DATA

} // namespace DB

#endif // PASSED_INFORMATION_MAP_H
