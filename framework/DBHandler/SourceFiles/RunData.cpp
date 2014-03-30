// Run Data - RunData.cpp (All data from "Run")
#include "../HeaderFiles/RunData.h"
#include <iostream>


namespace DB
{

namespace DATA
{

RunData::RunData() :
                    m_runStart(""),
                    m_filePath(""),
                    m_runDescription(""),
                    m_information("")
{
}

RunData::RunData(std::string p_runStart,
                 std::string p_filePath,
                 std::string p_runDescription,
                 std::string p_information) :
                                            m_runStart(p_runStart),
                                            m_filePath(p_filePath),
                                            m_runDescription(p_runDescription),
                                            m_information(p_information)
{
}

RunData::RunData(const RunData &p_runDataObject)
{
  m_runStart = p_runDataObject.m_runStart;
  m_filePath = p_runDataObject.m_filePath;
  m_runDescription = p_runDataObject.m_runDescription;
  m_information = p_runDataObject.m_information;
}

RunData& RunData::operator=(const RunData &p_runDataObject)
{
  m_runStart = p_runDataObject.m_runStart;
  m_filePath = p_runDataObject.m_filePath;
  m_runDescription = p_runDataObject.m_runDescription;
  m_information = p_runDataObject.m_information;

  return *this;
}

bool RunData::operator==(const RunData &p_runDataObject)
{
  bool l_equalCondition = false;
  l_equalCondition = (
                      m_runStart == p_runDataObject.m_runStart &&
                      m_filePath == p_runDataObject.m_filePath &&
                      m_runDescription == p_runDataObject.m_runDescription &&
                      m_information == p_runDataObject.m_information
                     );

  return l_equalCondition;
}

bool RunData::operator!=(const RunData &p_runDataObject)
{
  bool l_equalCondition = (*this == p_runDataObject);
  return ((l_equalCondition == true) ? false : true);
}

RunData::~RunData()
{

}

std::string RunData::runStart() const
{
  return m_runStart;
}

std::string RunData::filePath() const
{
  return m_filePath;
}

std::string RunData::runDescription() const
{
  return m_runDescription;
}

std::string RunData::information() const
{
  return m_information;
}

std::ostream& operator<< (std::ostream &p_stream, RunData const &p_runDataObject)
{
  p_stream << "runstart = " << p_runDataObject.m_runStart.c_str() << ", filepath = " << p_runDataObject.m_filePath.c_str() << ", rundescription = " << p_runDataObject.m_runDescription.c_str() << ", information = " << p_runDataObject.m_information.c_str() << std::endl;
  return p_stream;
}

std::ofstream& operator<< (std::ofstream &p_ofstream, RunData const &p_runDataObject)
{
  p_ofstream << p_runDataObject.m_runStart.c_str() << p_runDataObject.m_filePath.c_str() << p_runDataObject.m_runDescription.c_str() << p_runDataObject.m_information.c_str() << std::endl;
  return p_ofstream;
}

} // namespace DATA

} // namespace DB
