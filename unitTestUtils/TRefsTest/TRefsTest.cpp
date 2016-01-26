#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TRefsTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include  "TestEvent.h"
#include "FakeParamBank.h"

#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TList.h>
#include <TTree.h>
#include <TClonesArray.h>

/// some helper functions
void printIds(const TestEvent& event)
{
  std::cout << "event Id:" << event.getId() << std::endl;
  TestEvent* pEvent = event.getRefEvent();
  if (pEvent) {
    std::cout << "it points to event with Id:" << pEvent->getId() << std::endl;
  }
  size_t  size = event.getNbSubEvents();
  for (int i = 0; i < size; i++) {
    std::cout << "subevent id " << event.getSubEvent(i).getId()  << std::endl;
    pEvent = event.getSubEvent(i).getRefEvent();
    std::cout << "it points to event with Id:" << pEvent->getId() << std::endl;
  }
}

TFile* closeAndDeleteTFile(TFile* file)
{
  if (file) {
    file->Close();
    delete file;
  }
  return 0;
}

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  TestEvent paramObj(0, 1);
  TestEvent dataObj(&paramObj, 2);

  BOOST_REQUIRE(paramObj.getId() == 1);
  TestEvent* pEvent = dataObj.getRefEvent();
  BOOST_REQUIRE(paramObj.getId() == pEvent->getId());
  //printIds(dataObj);
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
    paramIndex = (paramIndex + 1) % kParamSize;
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

  TestEvent* b_eve = 0;
  dataTree->SetBranchAddress("TestEvent", &b_eve);
  for (int i = 0; i < kDataSize; i++) {
    dataTree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    dataTree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex);
    paramIndex = (paramIndex + 1) % kParamSize;
    //printIds(*b_eve);
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

  closeAndDeleteTFile(file);
  params = 0;
  dataTree = 0;

  file = new TFile ("data.root",  "READ", "", 0);
  TList* params2 = static_cast<TList*>(file->Get("params"));
  TTree* tree   = static_cast<TTree*>(file->Get("T"));

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params2->At(i))->getId() == i);
  }
  TestEvent* b_eve = 0;
  tree->SetBranchAddress("TestEvent", &b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
    //printIds(*b_eve);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex);
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  closeAndDeleteTFile(file);
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
  TestEvent* b_eve = 0;
  tree->SetBranchAddress("TestEvent", &b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex);
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  file = closeAndDeleteTFile(file);
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
  fileData = closeAndDeleteTFile(fileData);
  fileParam->WriteObject (params, "params");
  fileParam = closeAndDeleteTFile(fileParam);
  params = 0;
  dataTree = 0;

  fileParam = new TFile ("param2.root",  "READ", "", 0);
  TList* params2 = static_cast<TList*>(fileParam->Get("params"));
  fileData = new TFile ("data2.root",  "READ", "", 0);
  TTree* tree   = static_cast<TTree*>(fileData->Get("T"));

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params2->At(i))->getId() == i);
  }
  TestEvent* b_eve = 0;
  tree->SetBranchAddress("TestEvent", &b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex);
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  fileData = closeAndDeleteTFile(fileData);
  fileParam = closeAndDeleteTFile(fileParam);
}


BOOST_AUTO_TEST_CASE( my_stlvector_TTree )
{
  /// std::vector contains objects and no pointers
  const int kParamSize = 4;
  const int kDataSize = 10;
  std::vector<TestEvent> params;
  TTree* dataTree  = new TTree ("T", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);


  for (int i = 0; i < kParamSize; i++) {
    params.push_back(TestEvent(0, i));
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    eve = new TestEvent(&params.at(paramIndex), kParamSize + i);
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
    BOOST_REQUIRE(params.at(i).getId() == i);
  }

  TestEvent* b_eve = 0;
  dataTree->SetBranchAddress("TestEvent", &b_eve);
  for (int i = 0; i < kDataSize; i++) {
    dataTree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    dataTree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == params.at(paramIndex).getId());
    paramIndex = (paramIndex + 1) % kParamSize;
  }
}


BOOST_AUTO_TEST_CASE( my_stlvector_subevents_TTree_TFile)
{
  const int kParamSize = 4;
  const int kDataSize = 10;
  const int kSubEventSize = 3;

  TList* params = new TList;
  TFile* file = new TFile ("data3.root", "RECREATE", "", 0);
  TTree* dataTree  = new TTree ("T", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);

  for (int i = 0; i < kParamSize; i++) {
    params->Add(new TestEvent(0, i));
  }
  int paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    eve = new TestEvent(static_cast<TestEvent*>(params->At(paramIndex)), kParamSize + i);

    int subParamIndex = 0; // params for subevents
    for (int k = 0; k < kSubEventSize; k++) {
      TestEvent subevent(static_cast<TestEvent*>(params->At(subParamIndex)) , kParamSize + kDataSize + i * kSubEventSize + k);
      eve->addSubEvent(subevent);
      subParamIndex = (subParamIndex + 1) % kParamSize;
    }
    dataTree->Fill();
    paramIndex = (paramIndex + 1) % kParamSize;
  }
  //paramObjects indices from 0 to 3
  //DataObjects indices from 4 to 13
  //SubDataObjects indices from 14 to ...
  // every data object contains theww subdata object
  // connections: Data4 -> Param0
  //              Data4 contains Sub14 -> Param0
  //              Data4 contains Sub15 -> Param1
  //              Data4 contains Sub16 -> Param2
  //              Data5 -> Param1
  //              Data5 contains Sub17 -> Param0
  //              Data5 contains Sub18 -> Param1
  //              Data5 contains Sub19 -> Param2
  //              Data6 -> Param2
  //              ....
  //              Data7 -> Param3
  //              ...
  //              Data8 -> Param0
  //              .....
  file->WriteObject (params, "params");
  file->Write();
  file = closeAndDeleteTFile(file);
  params = 0;
  dataTree = 0;

  file = new TFile ("data3.root",  "READ", "", 0);
  TList* params2 = static_cast<TList*>(file->Get("params"));
  TTree* tree   = static_cast<TTree*>(file->Get("T"));

  for (int i = 0; i < kParamSize; i++) {
    BOOST_REQUIRE(static_cast<TestEvent*>(params2->At(i))->getId() == i);
  }
  TestEvent* b_eve = 0;
  tree->SetBranchAddress("TestEvent", &b_eve);
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getId() == kParamSize + i);
  }
  paramIndex = 0;
  for (int i = 0; i < kDataSize; i++) {
    tree->GetEvent(i);
    BOOST_REQUIRE(b_eve->getRefEvent()->getId() == paramIndex);
    //printIds(*b_eve);
    int subParamIndex = 0; // params for subevents
    for (int k = 0; k < kSubEventSize; k++) {
      TestEvent subEvent =  b_eve->getSubEvent(k);
      BOOST_REQUIRE(subEvent.getId() == kParamSize + kDataSize + i * kSubEventSize + k);
      BOOST_REQUIRE(subEvent.getRefEvent()->getId() == subParamIndex );
      subParamIndex = (subParamIndex + 1) % kParamSize;
    }

    paramIndex = (paramIndex + 1) % kParamSize;
  }
  file = closeAndDeleteTFile(file);
}

/// based on Alek's example sent to ROOT forum
/// See http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=18865
/// and #547
BOOST_AUTO_TEST_CASE( trefs_after_close_file  )
{
  TFile file("data4.root", "RECREATE", "", 0);
  TNamed* A = new TNamed("A", "Object A");
  TRef B;
  B = A; // assign the TRef
  file.WriteObject( A , "A");
  file.WriteObject( &B , "B" );
  file.Close("R");

  delete A;

  TFile file2("data4.root", "READ");
  TNamed* A2 = (TNamed*)file2.Get("A");
  TRef* B2 = (TRef*)file2.Get("B");
  file2.Close("R");
  BOOST_REQUIRE(std::string(A2->GetTitle()) == "Object A");
  TNamed* A_referenced = (TNamed*)(B2->GetObject());  // dereference the TRef
  /// BOOST_REQUIRE(A_referenced)
  /// @error A_referenced == NULL
  /// It should be still valid:
  /// BOOST_REQUIRE(std::string(A_referenced->GetTitle()) =="Object A");
  /// But it is not, somehow closing TFile makes the TRef not-valid
}


/// Trying to reproduce the bug described in #635
/// If we:
/// 1.save some info with TRefs to a file,
/// 2.in the new process, read the info from file and
///   add some new info with TRef to the new file,
/// 3.read the same file and try to get
///   access to TREfs -> they are not valid anymore.
/// I use dataXX.root generated by createTestRootFile program
/// it corresponds to point 1
/// My final conclusion: this appears only in case of TClonesArray
/// and does not appear in case of TList (dynamically allocated)
/// It must be related with the badly generated streamer I think

BOOST_AUTO_TEST_CASE(saving_trefs_in_different_processes)
{
  TFile* file = new TFile("dataXX.root", "READ", "", 0);
  FakeParamBank* fakeParamBank = static_cast<FakeParamBank*>(file->Get("params"));
  TTree* treeOld   = static_cast<TTree*>(file->Get("T"));
  TestEvent* b_eve_old = 0;
  treeOld->SetBranchAddress("TestEvent", &b_eve_old);

  // new file with new tree
  TFile* fileout = new TFile("dataXX2.root", "RECREATE", "", 0);
  TTree* dataTree  = new TTree ("T2", "dataTree");
  TestEvent* eve = 0;
  dataTree->Branch("TestEvent", "TestEvent", &eve);

  //tests of the old param bank
  /// param id:1  <--- data event 10
  /// param id:2  <--- data event 20
  /// param id:1 is stored in TClonesArray
  /// param id:2 is stored in the TList*
  BOOST_REQUIRE(fakeParamBank->getParam(0).getId() == 1);
  BOOST_REQUIRE((static_cast<TestEvent*>(fakeParamBank->getList()->At(0)))->getId() == 2);

  treeOld->GetEvent(1);
  TestEvent event_old2 = *b_eve_old;
  BOOST_REQUIRE_EQUAL(event_old2.getId(), 20);

  TestEvent* ref = event_old2.getRefEvent();
  BOOST_REQUIRE(ref);
  BOOST_REQUIRE_EQUAL(ref->getId(), 2);

  treeOld->GetEvent(0);
  TestEvent event_old = *b_eve_old;
  BOOST_REQUIRE_EQUAL(event_old.getId(), 10);

  //taking the reference from the object on TClonesArray
  ref = event_old.getRefEvent();
  ///This test does not pass cause somehow the ref is not valid when
  ///params are stored in TClonesArray and they were saved in different
  ///process - or program invokation
  //BOOST_REQUIRE(ref);
  //BOOST_REQUIRE_EQUAL(ref->getId(), 1);

  ///Now we adding events to the new tree.
  /// I try different methods to be sure that it does not affect the results.
  eve = &event_old;
  dataTree->Fill();
  TestEvent event_new = event_old2;
  eve = &event_old2;
  dataTree->Fill();
  ///New event to TClonesArray
  TestEvent* pParam = new TestEvent(0, 3);
  fakeParamBank->addParam(*pParam);
  eve = new TestEvent(pParam, 30);
  dataTree->Fill();
  /// New event to TList
  pParam = new TestEvent(0, 4);
  TList* paramList = fakeParamBank->getList();
  paramList->Add(pParam);
  eve = new TestEvent(static_cast<TestEvent*>(paramList->At(1)), 40);
  dataTree->Fill();
  ///some global cross-checks
  BOOST_REQUIRE_EQUAL(fakeParamBank->getParamsSize(), 2);
  BOOST_REQUIRE_EQUAL(fakeParamBank->getList()->GetSize(), 2);
  BOOST_REQUIRE_EQUAL(dataTree->GetEntries(), 4);
  ///saving and cleaning
  fileout->WriteObject(fakeParamBank, "params2");
  fileout->Write();
  closeAndDeleteTFile(file);
  closeAndDeleteTFile(fileout);
  delete fakeParamBank;
  delete pParam;

  /// We open a new file and try to read the param bank
  TFile fileout2("dataXX2.root", "READ", "", 0);
  FakeParamBank* fakeParamBank2 = static_cast<FakeParamBank*>(fileout2.Get("params2"));

  TTree* tree = static_cast<TTree*>(fileout2.Get("T2"));
  assert(tree);
  eve = 0;
  tree->SetBranchAddress("TestEvent",  &eve);

  BOOST_REQUIRE_EQUAL(fakeParamBank2->getParamsSize(), 2);
  BOOST_REQUIRE_EQUAL(fakeParamBank2->getList()->GetSize(), 2);
  BOOST_REQUIRE_EQUAL(tree->GetEntries(), 4);
  //tests of the new param bank
  /// param id:1  <--- data event 10
  /// param id:2  <--- data event 20
  /// param id:3  <--- data event 30
  /// param id:4  <--- data event 40
  /// param id:1 and 3 are stored in TClonesArray
  /// param id:2 and 4 are stored in the TList*
  BOOST_REQUIRE_EQUAL(fakeParamBank2->getParam(0).getId(), 1);
  BOOST_REQUIRE_EQUAL(fakeParamBank2->getParam(1).getId(), 3);
  BOOST_REQUIRE_EQUAL((static_cast<TestEvent*>(fakeParamBank2->getList()->At(0)))->getId(),  2);
  BOOST_REQUIRE_EQUAL((static_cast<TestEvent*>(fakeParamBank2->getList()->At(1)))->getId(),  4);

  tree->GetEvent(0); // id:10
  ref = eve->getRefEvent();
  // It does not work cause from TClonesArray which was written before
  // in a separate process
  // BOOST_REQUIRE(ref);
  BOOST_REQUIRE(!ref);
  //BOOST_REQUIRE_EQUAL(ref->getId(),1);
  tree->GetEvent(1); // id:20
  ref = eve->getRefEvent();
  BOOST_REQUIRE(ref);
  BOOST_REQUIRE_EQUAL(ref->getId(), 2);
  tree->GetEvent(2); // id:30
  ref = eve->getRefEvent();
  BOOST_REQUIRE(ref);
  BOOST_REQUIRE_EQUAL(ref->getId(), 3);
  tree->GetEvent(3); // id:40
  ref = eve->getRefEvent();
  BOOST_REQUIRE(ref);
  BOOST_REQUIRE_EQUAL(ref->getId(), 4);

  fileout2.Close("R");
}

BOOST_AUTO_TEST_SUITE_END()
