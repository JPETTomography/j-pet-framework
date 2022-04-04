/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetMatrixTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetMatrixTest

#include "JPetMatrix/JPetMatrix.h"
#include "JPetMatrix/JPetMatrixFactory.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(MatrixTestSuite)

BOOST_AUTO_TEST_CASE(constructors)
{
  JPetMatrix matrix1;
  BOOST_REQUIRE_EQUAL(matrix1.getID(), -1);
  BOOST_REQUIRE_EQUAL(matrix1.getSide(), JPetMatrix::SideA);
  BOOST_REQUIRE(!matrix1.isNullObject());

  JPetMatrix matrix2(123, JPetMatrix::SideB);
  BOOST_REQUIRE_EQUAL(matrix2.getID(), 123);
  BOOST_REQUIRE_EQUAL(matrix2.getSide(), JPetMatrix::SideB);
  BOOST_REQUIRE(!matrix2.isNullObject());

  JPetMatrix matrix3(true);
  BOOST_REQUIRE(matrix3.isNullObject());
}

BOOST_AUTO_TEST_CASE(set_get_tests)
{
  JPetScin scin(123, 50.0, 30.5, 12.3, 0.5, -12.3, 44.4, 1.0, 23.0, 49.0);
  JPetMatrix matrix;
  matrix.setID(234);
  matrix.setSide(JPetMatrix::SideB);
  matrix.setScin(scin);
  BOOST_REQUIRE_EQUAL(matrix.getID(), 234);
  BOOST_REQUIRE_EQUAL(matrix.getSide(), JPetMatrix::SideB);
  BOOST_REQUIRE_EQUAL(matrix.getScin().getID(), 123);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixFactorySuite)

class TestParamGetter : public JPetParamGetter
{

  ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runID)
  {
    ParamObjectsDescriptions result;
    switch (type)
    {
    case ParamObjectType::kMatrix:
      switch (runID)
      {
      // No Matrices
      case 0:
        break;
      // Single object
      case 1:
        result = {{1, {{"id", "1"}, {"side", "B"}, {"scin_id", "1"}}}};
        break;
      // Two objects
      case 2:
        result = {{1, {{"id", "1"}, {"side", "B"}, {"scin_id", "1"}}}, {5, {{"id", "5"}, {"side", "A"}, {"scin_id", "1"}}}};
        break;
      // Missing field
      case 3:
        result = {{1, {{"id", "1"}, {"scin_id", "1"}}}};
        break;
      // Wrong field
      case 4:
        result = {{1, {{"id", "first"}, {"side", "B"}, {"scin_id", "1"}}}};
        break;
      // Wrong relation
      case 5:
        result = {{1, {{"id", "1"}, {"side", "B"}, {"scin_id", "123"}}}};
        break;
      }
      break;
    case ParamObjectType::kScin:
      result = {{1,
                 {{"id", "1"},
                  {"length", "50.0"},
                  {"height", "15.0"},
                  {"width", "7.0"},
                  {"xcenter", "5.0"},
                  {"ycenter", "-5.0"},
                  {"zcenter", "15.0"},
                  {"rot_x", "90.0"},
                  {"rot_y", "45.0"},
                  {"rot_z", "60.0"},
                  {"slot_id", "1"}}}};
      break;
    case ParamObjectType::kSlot:
      result = {{1, {{"id", "1"}, {"theta", "5.5"}, {"type", "module"}, {"layer_id", "1"}}}};
      break;
    case ParamObjectType::kLayer:
      result = {{1, {{"id", "1"}, {"name", "sorbet"}, {"radius", "10.5"}, {"setup_id", "1"}}}};
      break;
    case ParamObjectType::kSetup:
      result = {{1, {{"id", "1"}, {"description", "jpet"}}}};
      break;
    default:
      break;
    }
    return result;
  }

  ParamRelationalData getAllRelationalData(ParamObjectType type1, ParamObjectType, const int runID)
  {
    ParamRelationalData result;
    switch (type1)
    {
    case ParamObjectType::kMatrix:
      switch (runID)
      {
      // No relations
      case 0:
        break;
      // Single object
      case 1:
        result = {{1, 1}};
        break;
      // Two objects
      case 2:
        result = {{1, 1}, {5, 1}};
        break;
      // Wrong relation
      case 5:
        result = {{1, 43}};
        break;
      default:
        result = {{1, 1}};
        break;
      }
      break;
    default:
      result = {{1, 1}};
      break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE(no_matrix)
{
  JPetSetupFactory setupFactory(paramGetter, 0);
  JPetLayerFactory layerFactory(paramGetter, 0, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 0, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 0, slotFactory);
  JPetMatrixFactory matrixFactory(paramGetter, 0, scinFactory);
  auto& matrices = matrixFactory.getMatrices();
  BOOST_REQUIRE_EQUAL(matrices.size(), 0u);
}

BOOST_AUTO_TEST_CASE(single_object)
{
  JPetSetupFactory setupFactory(paramGetter, 1);
  JPetLayerFactory layerFactory(paramGetter, 1, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 1, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 1, slotFactory);
  JPetMatrixFactory matrixFactory(paramGetter, 1, scinFactory);
  auto& matrices = matrixFactory.getMatrices();
  BOOST_REQUIRE_EQUAL(matrices.size(), 1u);
  auto matrix = matrices[1];
  BOOST_REQUIRE_EQUAL(matrix->getID(), 1);
  BOOST_REQUIRE_EQUAL(matrix->getSide(), JPetMatrix::SideB);
  BOOST_REQUIRE_EQUAL(matrix->getScin().getID(), scinFactory.getScins().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(two_objects)
{
  JPetSetupFactory setupFactory(paramGetter, 2);
  JPetLayerFactory layerFactory(paramGetter, 2, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 2, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 2, slotFactory);
  JPetMatrixFactory matrixFactory(paramGetter, 2, scinFactory);
  auto& matrices = matrixFactory.getMatrices();
  BOOST_REQUIRE_EQUAL(matrices.size(), 2u);
  auto matrix = matrices[1];
  BOOST_REQUIRE_EQUAL(matrix->getID(), 1);
  BOOST_REQUIRE_EQUAL(matrix->getSide(), JPetMatrix::SideB);
  BOOST_REQUIRE_EQUAL(matrix->getScin().getID(), scinFactory.getScins().at(1)->getID());
  matrix = matrices[5];
  BOOST_REQUIRE_EQUAL(matrix->getID(), 5);
  BOOST_REQUIRE_EQUAL(matrix->getSide(), JPetMatrix::SideA);
  BOOST_REQUIRE_EQUAL(matrix->getScin().getID(), scinFactory.getScins().at(1)->getID());
}

BOOST_AUTO_TEST_CASE(missing_field)
{
  JPetSetupFactory setupFactory(paramGetter, 3);
  JPetLayerFactory layerFactory(paramGetter, 3, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 3, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 3, slotFactory);
  JPetMatrixFactory matrixFactory(paramGetter, 3, scinFactory);
  BOOST_REQUIRE_THROW(matrixFactory.getMatrices(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(wrong_field)
{
  JPetSetupFactory setupFactory(paramGetter, 4);
  JPetLayerFactory layerFactory(paramGetter, 4, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 4, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 4, slotFactory);
  JPetMatrixFactory matrixFactory(paramGetter, 4, scinFactory);
  BOOST_REQUIRE_THROW(matrixFactory.getMatrices(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE(wrong_relation)
{
  JPetSetupFactory setupFactory(paramGetter, 5);
  JPetLayerFactory layerFactory(paramGetter, 5, setupFactory);
  JPetSlotFactory slotFactory(paramGetter, 5, layerFactory);
  JPetScinFactory scinFactory(paramGetter, 5, slotFactory);
  JPetMatrixFactory matrixFactory(paramGetter, 5, scinFactory);
  BOOST_REQUIRE_THROW(matrixFactory.getMatrices(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
