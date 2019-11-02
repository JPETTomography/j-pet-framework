/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetRecoSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoSignalTest

#include "JPetRecoSignal/JPetRecoSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)

float epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
  JPetRecoSignal signal;
  BOOST_CHECK_CLOSE(signal.getAmplitude(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getDelay(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getOffset(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getCharge(), 0.f, epsilon);
  BOOST_CHECK_EQUAL(signal.getShape().size(), 0u);
}

BOOST_AUTO_TEST_CASE(ScalarFieldsTest)
{
  JPetRecoSignal signal;
  signal.setAmplitude(43.f);
  signal.setCharge(44.f);
  signal.setDelay(45.f);
  signal.setOffset(46.f);
  BOOST_CHECK_CLOSE(signal.getAmplitude(), 43.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getCharge(), 44.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getDelay(), 45.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getOffset(), 46.f, epsilon);
}

BOOST_AUTO_TEST_CASE(SignalShapePointsTest)
{
  JPetRecoSignal signal(502);
  for (int i = 501; i >= 0; i--) {
    signal.setShapePoint((double) i, i + 0.43);
  }
  const std::vector<shapePoint> & vec = signal.getShape();
  BOOST_CHECK_EQUAL(vec.size(), 502u);
  BOOST_CHECK_CLOSE(vec.front().time, 501.f, epsilon);
  BOOST_CHECK_CLOSE(vec.front().amplitude, 501.43f, epsilon);
  BOOST_CHECK_CLOSE(vec.back().time, 0.f, epsilon);
  BOOST_CHECK_CLOSE(vec.back().amplitude, 0.43f, epsilon);
}

BOOST_AUTO_TEST_CASE(SignalShapeSortingTest1)
{
  JPetRecoSignal signal(502);
  for (int i = 501; i >= 0; i--) {
    signal.setShapePoint((double) i, 0);
  }
  signal.sortShapePoints(JPetRecoSignal::ByTime);
  const std::vector<shapePoint> & vec = signal.getShape();
  BOOST_CHECK_CLOSE(vec.front().time, 0.f, epsilon);
  BOOST_CHECK_CLOSE(vec.back().time, 501.f, epsilon);
}

BOOST_AUTO_TEST_CASE(SignalShapeSortingTest2)
{
  JPetRecoSignal signal(502);
  for (int i = 501; i >= 0; i--) {
    signal.setShapePoint((double) 0, i);
  }
  signal.sortShapePoints(JPetRecoSignal::ByAmplitude);
  const std::vector<shapePoint> & vec = signal.getShape();
  BOOST_CHECK_CLOSE(vec.front().amplitude, 0.f, epsilon);
  BOOST_CHECK_CLOSE(vec.back().amplitude, 501.f, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
