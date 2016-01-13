// Serializable Map - SerializableMap.hpp (Wrapper)
#ifndef SERIALIZABLE_MAP_HPP
#define SERIALIZABLE_MAP_HPP

#include <map>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#ifndef __CINT__
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */

#include "../HeaderFiles/DBHandler.h"


namespace DB
{

namespace DATA
{

template <typename KEY_TYPE, typename VALUE_TYPE >
class SerializableMap : public boost::noncopyable
{
protected:
  DB::SERVICES::DBHandler &m_dbHandlerInstance;
  std::map<KEY_TYPE, VALUE_TYPE > m_map;
  std::string m_fileNameToSaveMap;

public:
  SerializableMap(std::string p_fileNameToSaveMap, SERVICES::DBHandler &l_dBHandler = SERVICES::DBHandler::getInstance());
  virtual ~SerializableMap(void);

  virtual void clearMap(void);
  virtual void eraseElementFromMap(KEY_TYPE p_key);
  virtual void showMap(void) const = 0;
  virtual boost::optional<VALUE_TYPE > valueFromMap(KEY_TYPE p_key) = 0;
  virtual size_t sizeOfMap(void) const;
  virtual void saveMapToFile(std::string p_fileName) = 0;
  virtual bool removeFileWithMap(void);
  virtual boost::optional<std::pair<KEY_TYPE, VALUE_TYPE > > firstElement(void) const;
  virtual bool empty(void) const;
};


template <typename KEY_TYPE, typename VALUE_TYPE >
SerializableMap<KEY_TYPE, VALUE_TYPE >::SerializableMap(std::string p_fileNameToSaveMap,
                                                        SERVICES::DBHandler& l_dBHandler) :
                                                                                          m_dbHandlerInstance(l_dBHandler),
                                                                                          m_fileNameToSaveMap(p_fileNameToSaveMap)
{
}

template <typename KEY_TYPE, typename VALUE_TYPE >
SerializableMap<KEY_TYPE, VALUE_TYPE >::~SerializableMap()
{
}

template <typename KEY_TYPE, typename VALUE_TYPE >
void SerializableMap<KEY_TYPE, VALUE_TYPE >::clearMap()
{
  m_map.clear();
}

template <typename KEY_TYPE, typename VALUE_TYPE >
void SerializableMap<KEY_TYPE, VALUE_TYPE >::eraseElementFromMap(KEY_TYPE p_key)
{
  typedef typename std::map<KEY_TYPE, VALUE_TYPE >::iterator IteratorType;
  IteratorType l_iter = m_map.find(p_key);

  if(l_iter != m_map.end())
  {
    m_map.erase(l_iter);
  }
}

template <typename KEY_TYPE, typename VALUE_TYPE >
size_t SerializableMap<KEY_TYPE, VALUE_TYPE >::sizeOfMap() const
{
  return m_map.size();
}

template <typename KEY_TYPE, typename VALUE_TYPE >
bool SerializableMap<KEY_TYPE, VALUE_TYPE >::removeFileWithMap()
{
  if(remove(m_fileNameToSaveMap.c_str()) != 0)
  {
    std::string l_errorMessage = "Error while deleting file : " + m_fileNameToSaveMap;

    perror(l_errorMessage.c_str());
  }
  return 0;
}

template <typename KEY_TYPE, typename VALUE_TYPE >
boost::optional<std::pair<KEY_TYPE, VALUE_TYPE > > SerializableMap<KEY_TYPE, VALUE_TYPE >::firstElement() const
{
  if(!m_map.empty())
  {
    return std::make_pair(m_map.begin()->first, m_map.begin()->second);
  }
  return boost::none;
}

template <typename KEY_TYPE, typename VALUE_TYPE >
bool SerializableMap<KEY_TYPE, VALUE_TYPE >::empty() const
{
  return m_map.empty();
}

} // namespace DATA

} // namespace DB

#endif // SERIALIZABLE_MAP_HPP
