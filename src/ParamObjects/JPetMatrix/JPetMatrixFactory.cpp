/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetMatrixFactory.cpp
 */

#include "JPetMatrix/JPetMatrixFactory.h"
#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

std::map<int, JPetMatrix*>& JPetMatrixFactory::getMatrices()
{
  if (!fInitialized)
  {
    initialize();
  }
  return fMatrices;
}

void JPetMatrixFactory::initialize()
{
  ParamObjectsDescriptions descriptions = fParamGetter.getAllBasicData(ParamObjectType::kMatrix, fRunID);
  if (descriptions.size() == 0)
  {
    ERROR(Form("No Matrices in run %i", fRunID));
    return;
  }
  for (auto description : descriptions)
  {
    fMatrices[description.first] = build(description.second);
  }
  fInitialized = true;
  ParamRelationalData relations = fParamGetter.getAllRelationalData(ParamObjectType::kMatrix, ParamObjectType::kScin, fRunID);
  for (auto relation : relations)
  {
    fMatrices[relation.first]->setScin(*fScinFactory.getScins().at(relation.second));
  }
}

JPetMatrix* JPetMatrixFactory::build(ParamObjectDescription data)
{
  try
  {
    int id = boost::lexical_cast<int>(data.at("id"));
    std::string sideStr = boost::lexical_cast<std::string>(data.at("side"));
    JPetMatrix::Side side = JPetMatrix::SideA;
    if (sideStr == "A")
    {
      side = JPetMatrix::SideA;
    }
    else if (sideStr == "B")
    {
      side = JPetMatrix::SideB;
    }
    return new JPetMatrix(id, side);
  }
  catch (const std::exception& e)
  {
    ERROR(Form("Failed to build Matrix with error: %s", e.what()));
    throw;
  }
  return new JPetMatrix(true);
}
