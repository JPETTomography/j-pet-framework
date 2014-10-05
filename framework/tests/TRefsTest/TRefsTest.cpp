#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TRefsTest
#include <boost/test/unit_test.hpp>
#include  "TestEvent.h"


#include <TFile.h>
#include <TList.h>
#include <TTree.h>


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  TestEvent paramObj(0, 1);
  TestEvent dataObj(&paramObj, 2);

  BOOST_REQUIRE(paramObj.getId() == 1);
  TestEvent* pEvent = dataObj.getRefEvent();
  BOOST_REQUIRE(paramObj.getId() == pEvent->getId());
}

BOOST_AUTO_TEST_CASE( my_vectors_N_to_M )
{
  const int kParamSize = 4;
  const int kDataSize = 10;
  std::vector<TestEvent> params;
  std::vector<TestEvent> data;
  for (int i = 0; i < kParamSize; i++) {
    params.push_back(TestEvent(0, i));
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    data.push_back(TestEvent(&(params.at(paramIndex)), kParamSize + i));
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  //paramObjects indices from 0 to 3
  //DataObjects indices from 4 to 13
  // connections: Data4 -> Param0
  //              Data5 -> Param1
  //              Data6 -> Param2
  //              Data7 -> Param3
  //              Data8 -> Param0
  //              .....

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(params.at(i).getId() == i);
  }
  for (int i = 0; i < kDataSize; i++) {
    BOOST_REQUIRE(data.at(i).getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    BOOST_REQUIRE(data.at(i).getRefEvent()->getId() == paramIndex); 
    paramIndex = (paramIndex +1)%kParamSize;
  }
}

BOOST_AUTO_TEST_CASE( my_TList_TTree )
{
  const int kParamSize = 4;
  const int kDataSize = 10;
  TList* params = new TList();
  TTree* dataTree  = new TTree ("T", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);


  for (int i = 0; i < kParamSize; i++) {
    params->Add(new TestEvent(0, i));
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    eve = new TestEvent(static_cast<TestEvent*>(params->At(paramIndex)), kParamSize + i);
    dataTree->Fill();
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  //paramObjects indices from 0 to 3
  //DataObjects indices from 4 to 13
  // connections: Data4 -> Param0
  //              Data5 -> Param1
  //              Data6 -> Param2
  //              Data7 -> Param3
  //              Data8 -> Param0
  //              .....

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params->At(i))->getId() == i);
  }

  TestEvent* b_eve=0;
  dataTree->SetBranchAddress("TestEvent",&b_eve);
  for (int i = 0; i < kDataSize; i++) {
    dataTree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    dataTree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex); 
    paramIndex = (paramIndex +1)%kParamSize;
  }
}


BOOST_AUTO_TEST_CASE( my_TList_TTree_saving_to_TFile)
{
  const int kParamSize = 4;
  const int kDataSize = 10;
  TList* params = new TList;
  TFile* file = new TFile ("data.root", "RECREATE", "", 0);
  TTree* dataTree  = new TTree ("T", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);


  for (int i = 0; i < kParamSize; i++) {
    params->Add(new TestEvent(0, i));
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    eve = new TestEvent(static_cast<TestEvent*>(params->At(paramIndex)), kParamSize + i);
    dataTree->Fill();
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  //paramObjects indices from 0 to 3
  //DataObjects indices from 4 to 13
  // connections: Data4 -> Param0
  //              Data5 -> Param1
  //              Data6 -> Param2
  //              Data7 -> Param3
  //              Data8 -> Param0
  //              .....
  file->WriteObject (params, "params");
  file->Write();
  file->Close();
  params =0;
  dataTree = 0;

  file = new TFile ("data.root",  "READ", "", 0);
  TList* params2 = static_cast<TList*>(file->Get("params"));
  TTree* tree   = static_cast<TTree*>(file->Get("T"));

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params2->At(i))->getId() == i);
  }
  TestEvent* b_eve=0;
  tree->SetBranchAddress("TestEvent",&b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex); 
    paramIndex = (paramIndex +1)%kParamSize;
  }
  file->Close();
  delete file;
}

BOOST_AUTO_TEST_CASE( my_TList_TTree_saving_to_TFile_only_read)
{
  const int kParamSize = 4;
  const int kDataSize = 10;

 //paramObjects indices from 0 to 3
  //DataObjects indices from 4 to 13
  // connections: Data4 -> Param0
  //              Data5 -> Param1
  //              Data6 -> Param2
  //              Data7 -> Param3
  //              Data8 -> Param0
  //              .....
  TFile* file = new TFile ("data.root",  "READ", "", 0);
  TList* params2 = static_cast<TList*>(file->Get("params"));
  TTree* tree   = static_cast<TTree*>(file->Get("T"));

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params2->At(i))->getId() == i);
  }
  TestEvent* b_eve=0;
  tree->SetBranchAddress("TestEvent",&b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex); 
    paramIndex = (paramIndex +1)%kParamSize;
  }
  file->Close();
  delete file;
}

BOOST_AUTO_TEST_CASE( my_TList_TTree_saving_to_separate_files)
{
  const int kParamSize = 4;
  const int kDataSize = 10;
  TList* params = new TList;
  TFile* fileParam = new TFile ("param2.root", "RECREATE", "", 0);
  TFile* fileData = new TFile ("data2.root", "RECREATE", "", 0);
  TTree* dataTree  = new TTree ("T", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);


  for (int i = 0; i < kParamSize; i++) {
    params->Add(new TestEvent(0, i));
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    eve = new TestEvent(static_cast<TestEvent*>(params->At(paramIndex)), kParamSize + i);
    dataTree->Fill();
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  //paramObjects indices from 0 to 3
  //DataObjects indices from 4 to 13
  // connections: Data4 -> Param0
  //              Data5 -> Param1
  //              Data6 -> Param2
  //              Data7 -> Param3
  //              Data8 -> Param0
  //              .....
  fileData->Write();
  fileData->Close();
  delete fileData;
  fileData = 0;
  fileParam->WriteObject (params, "params");
  fileParam->Close();
  delete fileParam;
  fileParam = 0;
  params =0;
  dataTree = 0;
  
  fileParam = new TFile ("param2.root",  "READ", "", 0);
  TList* params2 = static_cast<TList*>(fileParam->Get("params"));
  fileData = new TFile ("data2.root",  "READ", "", 0);
  TTree* tree   = static_cast<TTree*>(fileData->Get("T"));

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params2->At(i))->getId() == i);
  }
  TestEvent* b_eve=0;
  tree->SetBranchAddress("TestEvent",&b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex); 
    paramIndex = (paramIndex +1)%kParamSize;
  }
  fileData->Close();
  delete fileData;
  fileParam->Close();
  delete fileParam;
}

BOOST_AUTO_TEST_SUITE_END()
