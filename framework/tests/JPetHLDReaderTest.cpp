#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHLDTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetHLDReader/JPetHLDReader.h"

// public:
//  JPetHLDReader();
//  explicit JPetHLDReader(const char* filename);
//  virtual ~JPetHLDReader();
//
//  void CloseFile();
//  long long GetEntries () const { return fTree->GetEntries(); }
//  int GetEntry (int entryNo) { return fTree->GetEntry(entryNo); }
//  bool OpenFile(const char* filename);
//  void ReadData();
//  TSlot& GetData() { return *fTSlot; }


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE(tt )
{
}


BOOST_AUTO_TEST_SUITE_END()
