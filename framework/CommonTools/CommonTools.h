// Common tools
#ifndef COMMON_TOOLS_H
#define COMMON_TOOLS_H

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>



class CommonTools : public boost::noncopyable
{
public:
  static const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
  }

  static std::size_t findSubstring(const std::string& p_string, const std::string& p_substring) {
    // TODO check extension of the file. If necessary change it to another.
    return p_string.find(p_substring);
  }

  static std::string Itoa(int x) {
    return intToString(x);
  }

  static std::string intToString(int x) {
    std::ostringstream out;
    out << x;
    return out.str();
  }
  static std::string doubleToString(double x) {
    std::ostringstream out;
    out << x;
    return out.str();
  }
  static int stringToInt(const std::string& str) {
    std::istringstream in(str);
    int num;
    in >> num;
    return num;
  }

  static bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
  }

  static bool ifFileExisting(const std::string& name) {
    std::ifstream f(name.c_str());
    if (f.good()) {
      f.close();
      return true;
    }
    f.close();
    return false;
  }

/**
 * @brief returns the time std::string in the format dd.mm.yyyy HH:MM
 */
static std::string getTimeString()
{
  time_t _tm = time(NULL );
  struct tm* curtime = localtime ( &_tm );
  char buf[100];
  strftime( buf, 100, "%d.%m.%Y %R", curtime);

  return std::string( buf );
}

};



#endif // COMMON_TOOLS_H
