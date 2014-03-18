// Param Server - ParamServer.h (Parameter Server)
#ifndef PARAM_SERVER_H
#define PARAM_SERVER_H

#include <map>
#include <utility>
#include <string>
#include <boost/optional.hpp>
//#include "../HeaderFiles/Declarations.h"
#include "../HeaderFiles/DBHandler.h"
#include "../HeaderFiles/RunData.h"


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
  std::map<int, DATA::RunData> m_runDataMap;
  std::string m_fileNameToSavePhotoMultiplierMap;

  int connectToDatabase(void);
  int disconnectFromDatabase(void);

  virtual void clearPhotoMultiplierMap(void);
  virtual void clearRunDataMap(void);
  virtual void eraseElementFromPhotoMultiplierMap(int p_slotId);
  virtual void eraseElementFromRunDataMap(int p_run_id);

public:
  virtual void fillPhotoMultiplierMap(void);
  virtual void fillRunDataMap(void);
  virtual void showPhotoMultiplierMap(void) const;
  virtual void showRunDataMap(void) const;
  virtual boost::optional<std::pair<int, int> > pairOfPhotoMultiplierForSlotId(int p_slotId);
  virtual boost::optional<DATA::RunData> dataFromRun(int p_run_id);
  virtual size_t sizeOfPhotoMultiplierMap(void) const;
  virtual size_t sizeOfRunDataMap(void) const;
  virtual void savePhotoMultiplierMapToFile(std::string p_fileName = "PhotoMultiplierMap.txt");
  virtual bool removeFileWithPhotoMultiplierMap(void);
};

} // namespace SERVER

} // namespace DB

#endif // PARAM_SERVER_H
