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
 *  @file PetDict.h
 */

#ifndef ______PET__DICT___H_________
#define ______PET__DICT___H_________
#include "./JPetGeomMappingInterface/JPetGeomMappingInterface.h"
#include <functional>
#include <vector>

template<typename SOURCE, int code = 0>
class Exception: public std::exception
{
private:
  std::string m_msg;
public:
  Exception(std::string&& msg) {
    m_msg = msg;
  }
  virtual ~Exception() throw() {}
  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};
template<class DataType>
class JPetMap
{
private:
  std::vector<std::vector<DataType>> f_data;
public:
  JPetMap(const std::vector<size_t>& layer_sizes) {
    size_t layer_index = 0;
    for (const size_t & item : layer_sizes) {
      f_data.push_back(std::vector<DataType>());
      for (size_t slot = 1; slot <= item; slot++) {
        DataType v;
        f_data[layer_index].push_back(v);
      }
      layer_index++;
    }
  }
  virtual ~JPetMap() {}
  void read(std::istream& str) {
    for (auto & layer : f_data)
      for (auto & item : layer)
        str >> item;
  }

  void save(std::ostream& str)const {
    for (const auto & layer : f_data)
      for (const auto & item : layer)
        str << item << "\n";
  }
  const size_t layersCount()const {
    return f_data.size();
  }
  const size_t layerSize(const size_t layer)const {
    if (layer == 0)throw Exception<JPetMap>("Invalid layer index");
    if (layer > f_data.size())throw Exception<JPetMap>("Invalid layer index");
    return f_data[layer - 1].size();
  }
  const size_t slotsCount()const {
    size_t res = 0;
    for (const auto & L : f_data)
      res += L.size();
    return res;
  }
  inline const size_t size()const {
    return slotsCount();
  }
  const size_t globalSlotNumber(const StripPos& pos)const {
    if (pos.layer == 0)throw Exception<JPetMap>("Invalid layer index");
    if (pos.layer > f_data.size())throw Exception<JPetMap>("Invalid layer index");
    if (pos.slot == 0)throw Exception<JPetMap>("Invalid slot index");
    if (pos.slot > f_data[pos.layer - 1].size())throw Exception<JPetMap>("Invalid slot index");
    size_t res = 0;
    for (size_t i = 1; i < pos.layer; i++)
      res += f_data[i - 1].size();
    return res + pos.slot - 1;
  }
  const StripPos positionOfGlobalNumber(const size_t gl_num)const {
    size_t index = gl_num;
    size_t l = 1;
    while (layerSize(l) <= index) {
      index -= layerSize(l);
      l++;
    }
    return {.layer = l, .slot = index + 1};
  }

  const DataType& operator[](const StripPos& pos)const {
    if (pos.layer == 0)throw Exception<JPetMap>("Invalid layer index");
    if (pos.layer > f_data.size())throw Exception<JPetMap>("Invalid layer index");
    if (pos.slot == 0)throw Exception<JPetMap>("Invalid slot index");
    if (pos.slot > f_data[pos.layer - 1].size())throw Exception<JPetMap>("Invalid slot index");
    return f_data[pos.layer - 1][pos.slot - 1];
  }
  const DataType& operator[](const size_t& pos)const {
    return operator[](positionOfGlobalNumber(pos));
  }
  DataType& item(const StripPos& pos) {
    if (pos.layer == 0)throw Exception<JPetMap>("Invalid layer index");
    if (pos.layer > f_data.size())throw Exception<JPetMap>("Invalid layer index");
    if (pos.slot == 0)throw Exception<JPetMap>("Invalid slot index");
    if (pos.slot > f_data[pos.layer - 1].size())throw Exception<JPetMap>("Invalid slot index");
    return f_data[pos.layer - 1][pos.slot - 1];
  }
  DataType& item(const size_t& pos) {
    return item(positionOfGlobalNumber(pos));
  }
};
template<class DataType>
inline std::istream& operator>>(std::istream& str, JPetMap<DataType>& item)
{
  item.read(str);
  return str;
}
template<class DataType>
inline std::ostream& operator<<(std::ostream& str, const JPetMap<DataType>& item)
{
  item.save(str);
  return str;
}
#endif
