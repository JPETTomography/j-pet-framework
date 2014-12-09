#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetWriterTest
#include <boost/test/unit_test.hpp>
#include <TNamed.h>

#define private public
#define protected public
#include "../../JPetWriter/JPetWriter.h"
#include "../../JPetReader/JPetReader.h"

//  JPetWriter(const char *p_fileName);
//  virtual ~JPetWriter(void);
//
//  template <class T>
//  bool Write(const T& obj);
//  template <class T>
//  bool Write(std::vector<T>& obj);
//  //bool OpenFile(const char* filename);
//  void WriteHeader(TObject* header);
//  inline bool IsOpenFile() const {return fFile.IsOpen();}
//  void closeFile();
//
//  int WriteObject(const TObject* obj, const char* name){ return fFile.WriteObject(obj, name); }
//  

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  JPetWriter writer("test.root");
  BOOST_REQUIRE(writer.isOpen());
  writer.closeFile();
  BOOST_REQUIRE(!writer.isOpen());
}

BOOST_AUTO_TEST_CASE( my_test2 )
{
  std::string fileName = "test2.root";
  JPetWriter writer(fileName.c_str());
  TNamed obj("TNamed", "Title of this testObj");
  writer.write(obj);
  writer.closeFile();
  
  JPetReader reader(fileName.c_str());
  BOOST_REQUIRE_EQUAL(reader.getEntries(), 1);
  reader.getEntry(0);
  TNamed& objOut = (TNamed&)reader.getData();
  BOOST_REQUIRE(std::string(objOut.GetName())=="TNamed");
  BOOST_REQUIRE(std::string(objOut.GetTitle())=="Title of this testObj");
}


/// a tree must have a name if not SetAutoSave makes it crash when when call Branch 
BOOST_AUTO_TEST_CASE( my_helperTest_for_test3 )
{
  std::string fileName = "test3_bis.root";
  TFile file(fileName.c_str(), "RECREATE");
  TTree tree("tree", "tree");  
  tree.SetAutoSave(1000);
  TNamed* filler = 0;
  tree.Branch("TNamed", "TNamed", &filler);
  const int kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    if (i%1000==0) std::cout<<"*"<<std::flush;
    TNamed obj("TNamed", Form("Title of this testObj%d",i));
    filler = &obj;
    tree.Fill();
    tree.FlushBaskets();
  }
  std::cout <<std::endl;
  file.Close();
}

BOOST_AUTO_TEST_CASE( my_test3 )
{
  std::string fileName = "test3.root";
  JPetWriter writer(fileName.c_str());
  const int kHugeNumberOfObjects = 10000;
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    TNamed obj("TNamed", Form("Title of this testObj%d",i));
    if (i%1000==0) std::cout<<"*"<<std::flush;
    writer.write(obj);
  }
  std::cout <<std::endl;
  writer.closeFile();
  
  JPetReader reader(fileName.c_str());
  BOOST_REQUIRE_EQUAL(reader.getEntries(), kHugeNumberOfObjects);
  for (int i = 0; i < kHugeNumberOfObjects; i++) {
    reader.getEntry(i);
    TNamed& objOut = (TNamed&)reader.getData();
    BOOST_REQUIRE(std::string(objOut.GetName())=="TNamed");
    BOOST_REQUIRE(std::string(objOut.GetTitle())==Form("Title of this testObj%d",i));
  }
}

BOOST_AUTO_TEST_SUITE_END()
