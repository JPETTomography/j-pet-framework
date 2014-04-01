// Serializable Map Boost Test - SerializableMapBT.hpp (Wrapper)
#ifndef SERIALIZABLE_MAP_BT_HPP
#define SERIALIZABLE_MAP_BT_HPP

#include "DBHandlerHelper.cpp"


namespace DB
{

namespace TEST
{

template <typename MAP_TYPE >
class SerializableMapBT : public boost::noncopyable
{
protected:
  SERVICES::DBHandler &m_dbHandlerInstance;
  MAP_TYPE *m_map;

  virtual int getFirstRunIdIfExist(void) const;
  virtual size_t getSizeOfRunTable(void) const;

public:
  SerializableMapBT(void);
  virtual ~SerializableMapBT(void);
};


template <typename MAP_TYPE >
SerializableMapBT<MAP_TYPE>::SerializableMapBT() :
                                                  m_dbHandlerInstance(DBHandlerHelper::getInstanceForTestsDemand()),
                                                  m_map(new MAP_TYPE(DBHandlerHelper::getInstanceForTestsDemand()))
{
}

template <typename MAP_TYPE >
SerializableMapBT<MAP_TYPE>::~SerializableMapBT()
{
  delete m_map;
}

template <typename MAP_TYPE >
int SerializableMapBT<MAP_TYPE>::getFirstRunIdIfExist() const
{
  std::string l_sqlQuerry = "SELECT * FROM runDataFunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    pqxx::result::const_iterator row = l_runDbResults.begin();
    int l_runId = row["run_id"].as<int>();

    return l_runId;
  }

  return -1;
}

template <typename MAP_TYPE >
size_t SerializableMapBT<MAP_TYPE>::getSizeOfRunTable() const
{
  std::string l_sqlQuerry = "SELECT * FROM runDataFunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);

  return l_runDbResults.size();
}

} // namespace TEST

} // namespace DB

#endif // SERIALIZABLE_MAP_BT_HPP
