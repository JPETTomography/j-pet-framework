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
 *  @file JPetAuxilliaryData.h
 */

#ifndef _JPET_AUXILLIARY_DATA_H_
#define _JPET_AUXILLIARY_DATA_H_

#include <TNamed.h>
#include <TString.h>
#include <vector>
#include <map>

/**
 * @brief A class wrapping a standard map and vector for passing arbitrary information between modules
 *
 * Objects if JPetAuxilliaryData type can be stored in a ROOT file so that they may be written by one module and later accessed by consecutive modules.
 *
 * These objects can be filled by the user with any information in the form of floating-point (double) values inside either a std::vector or std::map with string-type keys.
 *
 * The wrapper methods around vector and map involve safety checks to prevent the standard containers throwing exceptions. If a non-existing value is demanded with the getters, the JPetAuxilliaryData::Unset value is returned instead.
 *
 */
class JPetAuxilliaryData: public TNamed{

 public:
  JPetAuxilliaryData();
  JPetAuxilliaryData(std::string name);

  const static double Unset;
  
  void createVector(std::string name, int initial_size = 1000);
  void createMap(std::string name);

  /**
   * @brief insert a value into a vector/array type container
   *
   * The container with the given name must be created prior to calling this method.
   * If the name of non-existing container if provided or the index is outside of array bound, this method takes no effect.
   *
   */
  void setValue(std::string container_name, unsigned int index, double value);

  /**
   * @brief insert a value into a map/dictionary type container
   *
   * The container with the given name must be created prior to calling this method.
   * If the name of non-existing container if provided, this method takes no effect.
   *
   */
  void setValue(std::string container_name, std::string key, double value);
  
  /**
   * @brief extract a value from a vector/array type container
   *
   * If the container with the given name does not exist or the given index is outside of array bounds, this method will return the Unset constant.
   */
  double getValue(std::string container_name, unsigned int index) const;

  /**
   * @brief extract a value from a map/dictionary type container
   *
   * If the container with the given name does not exist or there is no record with the given key in the given container, this method will return the Unset constant.
   */
  double getValue(std::string container_name, std::string key) const;
  
  
 protected:
  std::map<std::string, std::vector<double> > fVectors;
  std::map<std::string, std::map<std::string, double> > fDictionaries;

  ClassDef(JPetAuxilliaryData, 1);
};

#endif
