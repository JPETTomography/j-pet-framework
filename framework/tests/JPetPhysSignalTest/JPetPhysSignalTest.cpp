#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPhysSignalTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetPhysSignal/JPetPhysSignal.h"
#include "../../JPetWriter/JPetWriter.h"
#include "../../JPetReader/JPetReader.h"

BOOST_AUTO_TEST_SUITE()

BOOST_AUTO_TEST_CASE( ConstructorTest ) {
  double epsilon = 1e-5;
  JPetPhysSignal signal;
  BOOST_CHECK_CLOSE(signal.getTime(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getQualityOfTime(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getPhe(), 0.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getQualityOfPhe(), 0.f, epsilon);
}

BOOST_AUTO_TEST_CASE( ScalarFieldsTest ) {
  double epsilon = 1e-5;
  JPetPhysSignal signal;
  signal.setTime(17.f);
  signal.setPhe(43.f);

  BOOST_CHECK_CLOSE(signal.getTime(), 17.f, epsilon);
  BOOST_CHECK_CLOSE(signal.getPhe(), 43.f, epsilon);
}

BOOST_AUTO_TEST_CASE( AllSignalsTest1 ) {

  // prepare raw signal
  JPetRawSignal raw(4);
  JPetSigCh sigch1(JPetSigCh::Leading, 17.f);
  sigch1.setThreshold(100);
  sigch1.setThresholdNumber(1);
  JPetSigCh sigch2(JPetSigCh::Leading, 43.f);
  sigch2.setThreshold(300);
  sigch2.setThresholdNumber(2);
  raw.addPoint(sigch1);
  raw.addPoint(sigch2);

  // prepare reco signal
  JPetRecoSignal reco;
  reco.setRawSignal(raw);
  for (int i = 501; i >= 0; i--) {
    reco.setShapePoint((double) i, i + 0.43f);
  }

  // prepare phys signal
  JPetPhysSignal phys;
  phys.setRecoSignal(reco);
  phys.setTime(42.42f);

  JPetWriter writer("signalTest.root");
  writer.write(phys);
  writer.closeFile();

}

BOOST_AUTO_TEST_CASE( AllSignalsTest2 ) {

  double epsilon = 1e-5;
  JPetReader reader;
  reader.openFile("signalTest.root");
  reader.readData();
  reader.getEntry(0);
  JPetPhysSignal & phys = (JPetPhysSignal&) reader.getData();
  BOOST_CHECK_CLOSE(phys.getTime(), 42.42f, epsilon);

  BOOST_CHECK_EQUAL(phys.getRecoSignal().getShape().size(), 502);
  BOOST_CHECK_CLOSE(phys.getRecoSignal().getShape().front().time, 501.f,
                    epsilon);
  BOOST_CHECK_CLOSE(phys.getRecoSignal().getShape().back().amplitude, 0.43f,
                    epsilon);

  const     JPetRawSignal & raw = phys.getRecoSignal().getRawSignal();
  BOOST_CHECK_EQUAL(raw.getNPoints(JPetSigCh::Leading), 2);
  BOOST_CHECK_CLOSE(
      raw.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).front().getThreshold(),
      100.f, epsilon);

}

BOOST_AUTO_TEST_SUITE_END()
