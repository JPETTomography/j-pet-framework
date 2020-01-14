/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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

 #include "JPetMatrixSignal/JPetMatrixSignal.h"
 #include <boost/test/unit_test.hpp>
 #include "JPetWriter/JPetWriter.h"
 #include "JPetReader/JPetReader.h"

 BOOST_AUTO_TEST_SUITE()

 float epsilon = 0.0001;

 BOOST_AUTO_TEST_CASE(ConstructorTest)
 {
   JPetMatrixSignal signal;
   BOOST_CHECK_CLOSE(signal.getTime(), 0.f, epsilon);
   BOOST_CHECK_CLOSE(signal.getTimeStdDev(), 0.f, epsilon);
   BOOST_CHECK_CLOSE(signal.getTOT(), 0.f, epsilon);
 }

 // TODO Make more test!!!

 BOOST_AUTO_TEST_SUITE_END()
