/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file CommonTools.h
 */

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

    template <typename Map>
    static bool mapComparator(Map const &lhs, Map const &rhs)
    {
        auto pred = [](decltype(*lhs.begin()) a, decltype(a) b)
                        {
                            return a.first == b.first
                                && a.second == b.second;
                        };

        return lhs.size() == rhs.size()
            && std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
    }
};



#endif // COMMON_TOOLS_H
