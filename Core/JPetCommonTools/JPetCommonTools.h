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
 *  @file JPetCommonTools.h
 */

#ifndef COMMON_TOOLS_H
#define COMMON_TOOLS_H

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */
#include <boost/filesystem.hpp>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <ctime>

/**
 * @brief Set of tools for general purposes
 */
class JPetCommonTools : public boost::noncopyable
{
public:
  static std::string extractDataTypeFromFileName(const std::string& filename);
  static std::vector<const char*> createArgs(const std::string& commandLine);
  static const std::string currentDateTime();
  static std::string doubleToString(double x);
  static int stringToInt(const std::string& str);
  static std::string replaceDataTypeInFileName(
    const std::string& filename,
    const std::string& newType
  );

  static std::string Itoa(int x)
  {
    return intToString(x);
  }

  static std::string intToString(int x)
  {
    std::ostringstream out;
    out << x;
    return out.str();
  }

  static bool to_bool(std::string str)
  {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
  }

  static bool ifFileExisting(const std::string& name)
  {
    std::ifstream f(name.c_str());
    if (f.good()) {
      f.close();
      return true;
    }
    f.close();
    return false;
  }

  /**
    * Returns the time std::string in the format dd.mm.yyyy HH:MM
    */
  static std::string getTimeString()
  {
    time_t _tm = time(NULL);
    struct tm* curtime = localtime ( &_tm );
    char buf[100];
    strftime( buf, 100, "%d.%m.%Y %R", curtime);
    return std::string( buf );
  }

  template <typename Map>
  static bool mapComparator(Map const& lhs, Map const& rhs)
  {
    auto pred = [](decltype(*lhs.begin()) a, decltype(a) b) {
      return a.first == b.first
             && a.second == b.second;
    };

    return lhs.size() == rhs.size()
           && std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
  }

  inline static std::string stripFileNameSuffix(const std::string& filename)
  {
    return  boost::filesystem::change_extension(filename, "").string();
  }

  inline static std::string exctractFileNameSuffix(const std::string& filename)
  {
    return boost::filesystem::extension(filename);
  }

  inline static std::string currentFullPath()
  {
    return boost::filesystem::path( boost::filesystem::current_path() ).string();
  }

  inline static std::string extractPathFromFile(const std::string& fileWithPath)
  {
    return boost::filesystem::path( fileWithPath ).parent_path().string();
  }

  inline static std::string extractFileNameFromFullPath(const std::string& fileWithPath)
  {
    return boost::filesystem::path( fileWithPath ).filename().string();
  }

  inline static std::string appendSlashToPathIfAbsent(const std::string& path)
  {
    if (!path.empty() && path.back() != '/') return path + '/';
    else return path;
  }

  inline static bool isDirectory( const std::string& dir)
  {
    return boost::filesystem::is_directory(dir);
  }

};

#endif /* !COMMON_TOOLS_H */
