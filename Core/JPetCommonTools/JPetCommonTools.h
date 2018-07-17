/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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

  /// Function extracts from the file name a substring that corresponds to the data type.
  /// according to the J-PET convention.
  /// E.g. for input filename  file.data.type.can.have.several.dots.root
  /// the returned data type should be "ata.type.can.have.several.dots"
  /// The ".root" suffix is obligatory.
  /// In other cases empty string is returned.
  static std::string extractDataTypeFromFileName(const std::string& filename);

  /// Function generates new file name by replacing the existing data type string
  /// by the new newType string.
  /// There are two different cases:
  /// 1) the original filename contains ".hld" suffix. Then
  /// the suffix is replaced by newType + ".root"
  /// 2) the original filename contains ".root" suffix. Then
  /// the oldType +".root" is replaced by newType+".root"
  static std::string replaceDataTypeInFileName(const std::string& filename, const std::string& newType);

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


/// This code below is the implementation of the make_pointer construct that is missing in C++11
/// In C++14 and greater the std::make_unique should be used
/// The code is the copy of  Stephan T. Lavavej code proposed here and later incorporated into C++14 standard.
/// See the source here: https://isocpp.org/files/papers/N3656.txt 
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>


namespace  jpet_common_tools
{
  template<class T> struct _Unique_if {
    typedef std::unique_ptr<T> _Single_object;
  };

  template<class T> struct _Unique_if<T[]> {
    typedef std::unique_ptr<T[]> _Unknown_bound;
  };

  template<class T, size_t N> struct _Unique_if<T[N]> {
    typedef void _Known_bound;
  };

  template<class T, class... Args>
    typename _Unique_if<T>::_Single_object
    make_unique(Args&&... args) {
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

  template<class T>
    typename _Unique_if<T>::_Unknown_bound
    make_unique(size_t n) {
      typedef typename std::remove_extent<T>::type U;
      return std::unique_ptr<T>(new U[n]());
    }

  template<class T, class... Args>
    typename _Unique_if<T>::_Known_bound
    make_unique(Args&&...) = delete;
}
#endif // COMMON_TOOLS_H
