// Param Server - ParamServer.h (Parameter Server)
#ifndef PARAM_SERVER_H
#define PARAM_SERVER_H

#include <map>
#include <utility>
#include <string>
#include <boost/optional.hpp>
#include "../HeaderFiles/Declarations.h"
#include "../HeaderFiles/DBHandler.h"


namespace DB
{

namespace SERVER
{

class ParamServer
{
public:
  ParamServer(void);
  ParamServer(DB::SERVICES::DBHandler &p_dbHandlerInstance);  // for the purposes of a test
  ParamServer(const ParamServer &p_paramServer) = delete;             // do przemyslenia!
  ParamServer& operator=(const ParamServer &p_paramServer) = delete;  // do przemyslenia!
  ParamServer(ParamServer &&p_paramServer) = delete;                  // do przemyslenia!
  ParamServer& operator=(ParamServer &&p_paramServer) = delete;       // do przemyslenia!
  virtual ~ParamServer(void);

protected:
  DB::SERVICES::DBHandler &m_dbHandlerInstance;

  std::map<int, std::pair<int, int > > m_photoMultiplierMap;
  std::string m_fileNameToSavePhotoMultiplierMap;

  int connectToDatabase(void);
  int disconnectFromDatabase(void);

public:
  virtual void fillPhotoMultiplierMap(void);
  virtual void showMap(void) const;
  virtual boost::optional<std::pair<int, int> > pairOfPhotoMultiplierForSlotId(int p_slotId);
  virtual void savePhotoMultiplierMapToFile(std::string p_fileName = "PhotoMultiplierMap.txt");
  virtual size_t sizeOfPhotoMultiplierMap(void) const;
  virtual bool removeFileWithPhotoMultiplierMap(void);
};

} // namespace SERVER

} // namespace DB

#endif // PARAM_SERVER_H
