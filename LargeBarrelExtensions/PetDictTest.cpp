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
 *  @file PetDictTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCmdParserTest
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include <random>
#include "PetDict.h"
using namespace std;
BOOST_AUTO_TEST_SUITE(JPetMapTesting)

BOOST_AUTO_TEST_CASE(empty){
    JPetMap<size_t> map({});
    BOOST_REQUIRE_EQUAL(0,map.LayersCount());
    BOOST_CHECK_THROW(map.LayerSize(0),Exception<JPetMap<size_t>>);
    BOOST_CHECK_THROW(map.LayerSize(1),Exception<JPetMap<size_t>>);
    BOOST_CHECK_THROW(map.LayerSize(2),Exception<JPetMap<size_t>>);
}
BOOST_AUTO_TEST_CASE(sizes){
    {
	JPetMap<size_t> map({2});
	BOOST_CHECK_THROW(map.LayerSize(0),Exception<JPetMap<size_t>>);
	BOOST_REQUIRE_EQUAL(2,map.LayerSize(1));
	BOOST_CHECK_THROW(map.LayerSize(2),Exception<JPetMap<size_t>>);
    }{
	JPetMap<size_t> map({2,3});
	BOOST_CHECK_THROW(map.LayerSize(0),Exception<JPetMap<size_t>>);
	BOOST_CHECK_THROW(map.operator[]({.layer=0,.slot=0}),Exception<JPetMap<size_t>>);
	BOOST_CHECK_THROW(map.operator[]({.layer=0,.slot=1}),Exception<JPetMap<size_t>>);
	BOOST_REQUIRE_EQUAL(2,map.LayerSize(1));
	BOOST_CHECK_THROW(map.operator[]({.layer=1,.slot=0}),Exception<JPetMap<size_t>>);
	BOOST_CHECK_NO_THROW(map.operator[]({.layer=1,.slot=1}));
	BOOST_CHECK_NO_THROW(map.operator[]({.layer=1,.slot=2}));
	BOOST_CHECK_THROW(map.operator[]({.layer=1,.slot=3}),Exception<JPetMap<size_t>>);
	BOOST_REQUIRE_EQUAL(3,map.LayerSize(2));
	BOOST_CHECK_THROW(map.LayerSize(3),Exception<JPetMap<size_t>>);
    }{
	JPetMap<size_t> map({2,3,8});
	BOOST_CHECK_THROW(map.LayerSize(0),Exception<JPetMap<size_t>>);
	BOOST_REQUIRE_EQUAL(2,map.LayerSize(1));
	BOOST_REQUIRE_EQUAL(3,map.LayerSize(2));
	BOOST_REQUIRE_EQUAL(8,map.LayerSize(3));
	BOOST_CHECK_THROW(map.LayerSize(4),Exception<JPetMap<size_t>>);
    }
}
BOOST_AUTO_TEST_CASE(Positioning){
    JPetMap<size_t> map({2,3,8});
    const auto initpos=map.PositionOfGlobalNumber(0);
    BOOST_REQUIRE_EQUAL(initpos.layer,1);
    BOOST_REQUIRE_EQUAL(initpos.slot,1);
    BOOST_REQUIRE_EQUAL(0,map.GlobalSlotNumber(initpos));
    for(size_t cur=1;cur<map.size();cur++){
	const size_t prev=cur-1;
	const auto prevpos=map.PositionOfGlobalNumber(prev);
	const auto curpos=map.PositionOfGlobalNumber(cur);
	BOOST_REQUIRE_EQUAL(cur,map.GlobalSlotNumber(curpos));
	if(prevpos.layer==curpos.layer){
	    BOOST_REQUIRE_EQUAL(prevpos.slot+1,curpos.slot);
	}else{
	    if((prevpos.layer+1)==curpos.layer){
		BOOST_REQUIRE_EQUAL(1,curpos.slot);
		BOOST_REQUIRE_EQUAL(map.LayerSize(prevpos.layer),prevpos.slot);
	    }else BOOST_REQUIRE(false);
	}
    }
}
BOOST_AUTO_TEST_SUITE_END()
