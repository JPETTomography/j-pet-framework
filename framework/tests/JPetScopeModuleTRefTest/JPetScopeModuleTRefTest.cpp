#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetReaderTest
#define BOOST_TEST_LOG_LEVEL message
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include <cstddef>
#include <iostream>
#include <vector>

#include "../../JPetReader/JPetReader.h"
#include "../../JPetLOR/JPetLOR.h"
#include "../../JPetHit/JPetHit.h"
#include "../../JPetPhysSignal/JPetPhysSignal.h"
#include "../../JPetTreeHeader/JPetTreeHeader.h"
#include "../../JPetParamManager/JPetParamManager.h"

/* In order to see BOOST messages call test with --log_level parameter:
 * ./JPetScopeModuleTRefTest --log_level=message
 */

BOOST_AUTO_TEST_SUITE (FirstSuite)

BOOST_AUTO_TEST_CASE (check_JPetTreeHeader_in_output_of_JPetScopeModule)
{
  JPetReader reader("testfile.root");
  BOOST_REQUIRE(reader.isOpen());

  JPetTreeHeader* header = reader.getHeaderClone();
  BOOST_REQUIRE(header != 0);
  
  BOOST_MESSAGE("Source position: " << header->getSourcePosition());

  reader.closeFile();

}

BOOST_AUTO_TEST_CASE (check_TRefs_in_output_of_JPetScopeModule)
{
  JPetReader reader("testfile.root");
  BOOST_REQUIRE(reader.isOpen());

  JPetParamManager paramManager;
  BOOST_REQUIRE(paramManager.readParametersFromFile(&reader));

  const JPetParamBank& paramBank = paramManager.getParamBank();

  JPetLOR* lor = (JPetLOR*)&(reader.getData());
  const JPetHit* hit1;
  const JPetHit* hit2;
  const JPetPhysSignal* psig1;
  const JPetPhysSignal* psig2;
  const JPetPhysSignal* psig3;
  const JPetPhysSignal* psig4;
  const JPetPM* pm1;
  const JPetPM* pm2;
  const JPetPM* pm3;
  const JPetPM* pm4;
  JPetScin* scin1;
  JPetScin* scin2;

  for (int i = 0; i < reader.getEntries(); ++i) {
    
    BOOST_TEST_MESSAGE("Testing for event: " << i );

    reader.getEntry(i);
    BOOST_REQUIRE(lor != 0);

    hit1 = &(lor->getFirstHit());
    hit2 = &(lor->getSecondHit());
    BOOST_REQUIRE(hit1 != 0);
    BOOST_REQUIRE(hit2 != 0);

    psig1 = &(hit1->getSignalA());
    psig2 = &(hit1->getSignalB());
    psig3 = &(hit2->getSignalA());
    psig4 = &(hit2->getSignalB());
    BOOST_REQUIRE(psig1 != 0);
    BOOST_REQUIRE(psig2 != 0);
    BOOST_REQUIRE(psig3 != 0);
    BOOST_REQUIRE(psig4 != 0);

    pm1 = &(psig1->getPM());
    pm2 = &(psig2->getPM());
    pm3 = &(psig3->getPM());
    pm4 = &(psig4->getPM());

    BOOST_CHECK(pm1 != 0);
    BOOST_CHECK(pm2 != 0);
    BOOST_CHECK(pm3 != 0);
    BOOST_CHECK(pm4 != 0);

    if (pm1 != 0 && pm2 != 0) {
      BOOST_MESSAGE("PM1 id:   " << pm1->getID());
      BOOST_MESSAGE("PM2 id:   " << pm2->getID());

      scin1 = &(pm1->getScin());
      BOOST_CHECK(scin1 != 0);

      if (scin1 != 0) {
        BOOST_CHECK_EQUAL((pm1->getScin()).getID(), (pm2->getScin()).getID());
        BOOST_MESSAGE("SCIN1 id: " << scin1->getID());
      }

   }

    if (pm3 != 0 && pm3 != 0) {
      BOOST_MESSAGE("PM3 id:   " << pm3->getID());
      BOOST_MESSAGE("PM4 id:   " << pm4->getID());

      scin2 = &(pm3->getScin());
      BOOST_CHECK(scin2 != 0);

      if (scin2 != 0) {
        BOOST_CHECK_EQUAL((pm3->getScin()).getID(), (pm4->getScin()).getID());
        BOOST_MESSAGE("SCIN2 id: " << scin2->getID());
      }

    }
  
  }
  
}

BOOST_AUTO_TEST_SUITE_END()
