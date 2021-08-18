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
 *  @file JPetMatrixSignalTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetMatrixSignalTest

#include "Signals/JPetMatrixSignal/JPetMatrixSignal.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE()

double epsilon = 0.00001;

BOOST_AUTO_TEST_CASE(constructor_test)
{
  JPetMatrixSignal signal;
  BOOST_REQUIRE_CLOSE(signal.getTime(), 0.0, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Unknown);
  BOOST_REQUIRE_CLOSE(signal.getToT(), 0.0, epsilon);
}

BOOST_AUTO_TEST_CASE(adding_signals_test)
{
  JPetMatrixSignal signal;

  JPetPM pm1(1, "mtx_p1", 1);
  JPetPM pm2(2, "mtx_p2", 2);
  JPetPM pm3(3, "mtx_p3", 3);
  JPetPM pm4(4, "mtx_p4", 4);

  JPetPMSignal pms1;
  JPetPMSignal pms2;
  JPetPMSignal pms3;
  JPetPMSignal pms4;
  pms1.setPM(pm1);
  pms2.setPM(pm2);
  pms3.setPM(pm3);
  pms4.setPM(pm4);

  // Adding signals from different positions
  BOOST_REQUIRE(signal.addPMSignal(pms1));
  BOOST_REQUIRE(signal.addPMSignal(pms2));
  BOOST_REQUIRE(signal.addPMSignal(pms3));
  BOOST_REQUIRE(signal.addPMSignal(pms4));

  // Adding signal to already occupied matrix position
  BOOST_REQUIRE(!signal.addPMSignal(pms1));
  BOOST_REQUIRE(!signal.addPMSignal(pms2));
  BOOST_REQUIRE(!signal.addPMSignal(pms3));
  BOOST_REQUIRE(!signal.addPMSignal(pms4));
}

BOOST_AUTO_TEST_CASE(set_matrix_test)
{
  JPetMatrixSignal signal;
  BOOST_REQUIRE(signal.getMatrix().isNullObject());

  JPetMatrix mtx(11, JPetMatrix::SideB);
  signal.setMatrix(mtx);
  BOOST_REQUIRE(!signal.getMatrix().isNullObject());
  BOOST_REQUIRE_EQUAL(signal.getMatrix().getID(), 11);
  BOOST_REQUIRE_EQUAL(signal.getMatrix().getSide(), JPetMatrix::SideB);
}

BOOST_AUTO_TEST_CASE(time_and_tot_test)
{
  JPetMatrixSignal signal;
  signal.setTime(123.45);
  signal.setRecoFlag(JPetRecoSignal::Good);

  JPetPM pm1(1, "mtx_p1", 1);
  JPetPM pm2(2, "mtx_p2", 2);
  JPetPM pm3(3, "mtx_p3", 3);
  JPetPM pm4(4, "mtx_p4", 4);

  JPetPMSignal pms1;
  JPetPMSignal pms2;
  JPetPMSignal pms3;
  pms1.setPM(pm1);
  pms2.setPM(pm2);
  pms3.setPM(pm3);
  pms1.setToT(20.0);
  pms2.setToT(40.0);
  pms3.setToT(15.0);

  BOOST_REQUIRE_CLOSE(signal.getTime(), 123.45, epsilon);
  BOOST_REQUIRE_EQUAL(signal.getRecoFlag(), JPetRecoSignal::Good);

  // ToT of a matrix signal is a average of ToT of added PM Signals
  // None
  BOOST_REQUIRE_CLOSE(signal.getToT(), 0.0, epsilon);
  // One signal
  BOOST_REQUIRE(signal.addPMSignal(pms1));
  BOOST_REQUIRE_CLOSE(signal.getToT(), 20.0, epsilon);
  // Two signals
  BOOST_REQUIRE(signal.addPMSignal(pms2));
  BOOST_REQUIRE_CLOSE(signal.getToT(), 30.0, epsilon);
  // Three signals
  BOOST_REQUIRE(signal.addPMSignal(pms3));
  BOOST_REQUIRE_CLOSE(signal.getToT(), 25.0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
