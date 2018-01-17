#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetMCHitTest
#include <boost/test/unit_test.hpp>

#include "./JPetMCHit/JPetMCHit.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetBarrelSlot/JPetBarrelSlot.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetMCHit hit;
  double epsilon = 0.0001;

/// MC hit part

  BOOST_REQUIRE_EQUAL(hit.getMCDecayTreeIndex(), 0);
  BOOST_REQUIRE_EQUAL(hit.getMCVtxIndex(), 0);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().X(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Y(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Z(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getMomentum().X(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Y(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Z(), 0, epsilon );

/// JPetHit part
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);

  BOOST_REQUIRE_CLOSE(hit.getPosX(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPosY(), 0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), 0, epsilon );

  BOOST_REQUIRE_EQUAL(hit.isSignalASet(), false);
  BOOST_REQUIRE_EQUAL(hit.isSignalBSet(), false);
}

BOOST_AUTO_TEST_CASE(non_default_constructor)
{
  TVector3 position(6.0, 7.0, 8.0);
  TVector3 polarization(2.0, 3.0, 4.0);
  TVector3 momentum(1.0, -13.0, 13.0);
  auto MCDecayTreeIndex = 7;
  auto MCVtxIndex = 99;
  auto energy = 5.5;
  auto time  = 3.3;
  double epsilon = 0.0001;

  JPetMCHit hit(MCDecayTreeIndex, MCVtxIndex, energy , time, position, polarization, momentum);

  BOOST_REQUIRE_CLOSE(hit.getEnergy(), energy, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), time, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosX(), position.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosY(), position.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPosZ(), position.Z() , epsilon);

  /// MC-specific
  BOOST_REQUIRE_CLOSE(hit.getPolarization().X(), polarization.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Y(), polarization.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Z(), polarization.Z() , epsilon);

  BOOST_REQUIRE_CLOSE(hit.getMomentum().X(), momentum.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Y(), momentum.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Z(), momentum.Z() , epsilon);

  BOOST_REQUIRE_EQUAL(hit.getMCDecayTreeIndex(), MCDecayTreeIndex);
  BOOST_REQUIRE_EQUAL(hit.getMCVtxIndex(), MCVtxIndex);
}

BOOST_AUTO_TEST_CASE(getters_setters_mc)
{
  JPetMCHit hit;
  TVector3 pol(2.0, 3.0, 4.0);
  TVector3 mom(1.0, -13.0, 13.0);
  auto MCDecayTreeIndex = 7;
  auto MCVtxIndex = 99;
  double epsilon = 0.0001;
  hit.setPolarization(pol.X(), pol.Y(), pol.Z());
  hit.setMomentum(mom.X(), mom.Y(), mom.Z() );
  hit.setMCDecayTreeIndex(MCDecayTreeIndex);
  hit.setMCVtxIndex(MCVtxIndex);

  /// MC-specific
  BOOST_REQUIRE_CLOSE(hit.getPolarization().X(), pol.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Y(), pol.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getPolarization().Z(), pol.Z() , epsilon);

  BOOST_REQUIRE_CLOSE(hit.getMomentum().X(), mom.X(), epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Y(), mom.Y() , epsilon);
  BOOST_REQUIRE_CLOSE(hit.getMomentum().Z(), mom.Z() , epsilon);

  BOOST_REQUIRE_EQUAL(hit.getMCDecayTreeIndex(), MCDecayTreeIndex);
  BOOST_REQUIRE_EQUAL(hit.getMCVtxIndex(), MCVtxIndex);
}

BOOST_AUTO_TEST_SUITE_END()
