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
 *  @file JPetPhysSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysSignalTest

#include "JPetPhysSignal/JPetPhysSignal.h"
#include <boost/test/unit_test.hpp>
#include "JPetWriter/JPetWriter.h"
#include "JPetReader/JPetReader.h"

BOOST_AUTO_TEST_SUITE()

float epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
  JPetPhysSignal signal;
  BOOST_CHECK_CLOSE(signal.getTime(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getQualityOfTime(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getPhe(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getQualityOfPhe(), 0.f, epsilon);
}

BOOST_AUTO_TEST_CASE(ScalarFieldsTest)
{
  JPetPhysSignal signal;
  signal.setTime(17.f);
  signal.setQualityOfTime(1.f);
  signal.setPhe(43.f);
  signal.setQualityOfPhe(4.f);
  BOOST_CHECK_CLOSE(signal.getTime(), 17.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getQualityOfTime(), 1.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getPhe(), 43.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getQualityOfPhe(), 4.f, epsilon);
}

BOOST_AUTO_TEST_CASE(AllSignalsTest1)
{
  JPetChannel channel1(1, 1, 10.0);
  JPetChannel channel2(2, 1, 20.0);
  JPetSigCh sigCh1(JPetSigCh::Leading, 17.f);
  JPetSigCh sigCh2(JPetSigCh::Trailing, 43.f);
  JPetSigCh sigCh3(JPetSigCh::Leading, 27.f);
  JPetSigCh sigCh4(JPetSigCh::Trailing, 53.f);
  sigCh1.setChannel(channel1);
  sigCh2.setChannel(channel1);
  sigCh3.setChannel(channel2);
  sigCh4.setChannel(channel2);

  JPetRawSignal raw;
  raw.addPoint(sigCh1);
  raw.addPoint(sigCh2);
  raw.addPoint(sigCh3);
  raw.addPoint(sigCh4);

  JPetRecoSignal reco;
  reco.setRawSignal(raw);
  for (int i = 501; i >= 0; i--) {
    reco.setShapePoint((float) i, i + 0.43f);
  }

  JPetPhysSignal phys;
  phys.setRecoSignal(reco);
  phys.setTime(42.42f);

  JPetWriter writer("signalTest.root");
  writer.write(phys);
  writer.closeFile();
  BOOST_REQUIRE(!writer.isOpen());
}

BOOST_AUTO_TEST_CASE(AllSignalsTest2)
{
  JPetReader reader;
  reader.openFileAndLoadData("signalTest.root");
  JPetPhysSignal& phys = (JPetPhysSignal&) reader.getCurrentEntry();
  BOOST_CHECK_CLOSE(phys.getTime(), 42.42f, epsilon);
  BOOST_CHECK_EQUAL(phys.getRecoSignal().getShape().size(), 502u);
  BOOST_CHECK_CLOSE(
    phys.getRecoSignal().getShape().front().time, 501.f, epsilon
  );
  BOOST_CHECK_CLOSE(
    phys.getRecoSignal().getShape().back().amplitude, 0.43f, epsilon
  );
  const JPetRawSignal& raw = phys.getRecoSignal().getRawSignal();
  BOOST_CHECK_EQUAL(raw.getNumberOfPoints(JPetSigCh::Leading), 2);
  BOOST_CHECK_EQUAL(raw.getNumberOfPoints(JPetSigCh::Trailing), 2);
  auto leadPoints = raw.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue);
  auto trailPoints = raw.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrValue);
  BOOST_CHECK_CLOSE(leadPoints[0].getTime(), 17.0, epsilon);
  BOOST_CHECK_CLOSE(leadPoints[1].getTime(), 27.0, epsilon);
  BOOST_CHECK_CLOSE(trailPoints[0].getTime(), 43.0, epsilon);
  BOOST_CHECK_CLOSE(trailPoints[1].getTime(), 53.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
