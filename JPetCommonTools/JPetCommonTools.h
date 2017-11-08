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
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stdlib.h>

class JPetCommonTools : public boost::noncopyable
{
public:
  static const std::string currentDateTime();

  static std::size_t findSubstring(const std::string& p_string, const std::string& p_substring);

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

  static std::string doubleToString(double x);

  static int stringToInt(const std::string& str);

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
  static bool mapComparator(Map const& lhs, Map const& rhs)
  {
    auto pred = [](decltype(*lhs.begin()) a, decltype(a) b) {
      return a.first == b.first
             && a.second == b.second;
    };

    return lhs.size() == rhs.size()
           && std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
  }

  ///removes the suffix of the file
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

  static std::string extractDataTypeFromFile(const std::string& filename);
  static std::string replaceDataTypeInFile(const std::string& filename, const std::string& newType);
  
  inline static std::string appendSlashToPathIfAbsent(const std::string& path)
  {
    if (!path.empty() && path.back() != '/') return path + '/';
    else return path;
  }

  inline static bool isDirectory( const std::string& dir)
  {
    return boost::filesystem::is_directory(dir);
  }

  /// Creates a pair int and const char* arguments to emulate int arc, const char** argv parameters
  /// in commandLine="./blabla.x -p test" will be transformed to a array of
  /// const char c-strings "./blabla.x", "-p", "test"
  /// Watch out the returned array contains the dynamically allocated  c-strings
  /// of const char* that should be deallocated by delete to avoid the memory leak.
  static std::vector<const char*> createArgs(const std::string& commandLine);
};

#endif // COMMON_TOOLS_H
