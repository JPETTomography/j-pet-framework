// Run Data - RunData.h (All data from "Run")
#ifndef RUN_DATA_H
#define RUN_DATA_H

#include <string>
#include <fstream>


namespace DB
{

namespace DATA
{

class RunData
{
public:
  RunData(void);
  RunData(std::string p_runStart, std::string p_filePath, std::string p_runDescription, std::string p_information);
  RunData(const RunData &p_runDataObject);
  RunData& operator=(const RunData &p_runDataObject);
  bool operator==(const RunData &p_runDataObject);
  bool operator!=(const RunData &p_runDataObject);
  virtual ~RunData(void);

protected:
  std::string m_runStart;
  std::string m_filePath;
  std::string m_runDescription;
  std::string m_information;

public:
  virtual std::string runStart(void) const;
  virtual std::string filePath(void) const;
  virtual std::string runDescription(void) const;
  virtual std::string information(void) const;

  friend std::ostream& operator<< (std::ostream &p_stream, RunData const &p_runDataObject);
  friend std::ofstream& operator<< (std::ofstream &p_ofstream, RunData const &p_runDataObject);
};

} // namespace DATA

} // namespace DB

#endif // RUN_DATA_H
