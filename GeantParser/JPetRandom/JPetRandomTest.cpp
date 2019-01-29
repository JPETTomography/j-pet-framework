/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetRandomTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRandomTest
#include <boost/test/unit_test.hpp>

#include <JPetRandom/JPetRandom.h>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( checkSeed )
{
      TRandom3* ranGen = JPetRandom::GetRandomGenerator();

      unsigned long testSeed = 789764356;
      ranGen->SetSeed(testSeed);
      BOOST_REQUIRE_EQUAL(testSeed, ranGen->GetSeed() );

}

BOOST_AUTO_TEST_CASE( checkSingleInstance )
{
      TRandom3* ranGen = JPetRandom::GetRandomGenerator();
      TRandom3* ranGen2 = JPetRandom::GetRandomGenerator();

      BOOST_REQUIRE_EQUAL(ranGen, ranGen2 );

}


BOOST_AUTO_TEST_SUITE_END()

