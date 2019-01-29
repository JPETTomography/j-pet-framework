#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGATEConverterTest
#include <boost/test/unit_test.hpp>
#include "TString.h"
#include <vector>            
#include "JPetScin/JPetScin.h" 
#include "JPetGATEConverter.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  std::cout << "Converter test" << std::endl;
  TString root_file = "unitTestData/JPetGATEConverterTest/test_384strips.root";       
  bool dd;
  JPetGATEConverter conv; 
  dd = conv.converterJPetHit(root_file);                              
  BOOST_REQUIRE(!dd); 
}

BOOST_AUTO_TEST_CASE( default_c )            
{
  std::cout << "ConverterMC test" << std::endl;
  TString root_file = "unitTestData/JPetGATEConverterTest/output_192str_3lay_L050.root"; 
  std::string json_file = "unitTestData/JPetGATEConverterTest/detectorSetupRun2345.json"; 
  int run_id = 2;		 
  JPetGATEConverter conv(json_file,run_id);                    
  BOOST_REQUIRE_EQUAL(conv.converterJPetMCHit(root_file),true);  				
}

BOOST_AUTO_TEST_CASE( read_param_bank )            
{
  JPetGATEConverter conv; 
  JPetMCHit* MChit = NULL;
  int idStripTab[10];
  int id_strip;     
  TFile file1("unitTestData/JPetGATEConverterTest/output_192str_3lay_L050.root","READ");
   
  TTree *tree1 = (TTree*)file1.Get(conv.getfTreeName(0).c_str()); 
  tree1->SetBranchAddress("volumeID",&idStripTab);   

  TFile file2("unitTestData/JPetGATEConverterTest/output_192str_3lay_L050.gate.root", "READ");   
  TTree* tree2 = (TTree*)file2.Get("treemc"); 
  tree2->SetBranchAddress("JPetMCHit",&MChit); 

  Long64_t numbentries1 = tree1->GetEntries(); 
  Long64_t numbentries2 = tree2->GetEntries();

  BOOST_REQUIRE_EQUAL(numbentries1,numbentries2);
  
  for (Long64_t i=0; i < numbentries1; i=i+1)   
    {
       tree1->GetEntry(i); 
       id_strip = idStripTab[1]+ 1; 
       tree2->GetEntry(i);
       BOOST_REQUIRE_EQUAL(id_strip, MChit->getScintillator().getID());
    }
}

BOOST_AUTO_TEST_CASE( create_output_file_name) 
{ 
  JPetGATEConverter conv;
  BOOST_REQUIRE_EQUAL(conv.createOutputFileName("blabla.root"),"blabla.gate.root"); 
  BOOST_REQUIRE_EQUAL(conv.createOutputFileName("abcd.root"),"abcd.gate.root"); 
  BOOST_REQUIRE_EQUAL(conv.createOutputFileName("jkl.root"),"jkl.gate.root"); 
}

BOOST_AUTO_TEST_CASE(check_argument)
{
  JPetGATEConverter conv;	
  BOOST_REQUIRE(conv.checkArgument("blabla.root")); 
  BOOST_REQUIRE(conv.checkArgument("abc.root"))	;   

} 

BOOST_AUTO_TEST_CASE(tree_indicators_test)  
{
  JPetGATEConverter conv;
  TString root_file = "unitTestData/JPetGATEConverterTest/output_192str_3lay_L050.root";  //inputType named FirstGate
  //TString root_file = "unitTestData/JPetGATEConverterTest/GlobalActorOutputFile/GlobalActorExampleFile.root"; //inputType named SecondGate
  TFile *f = new TFile(root_file); 
   TTree *t_test = (TTree*)f->Get(conv.getfTreeName(0).c_str()); 
  if(t_test != NULL)
  {
    conv.finputType = kFirstGate;
  }

  t_test = (TTree*)f->Get(conv.getfTreeName(1).c_str()); 
  if(t_test != NULL)
  {
    conv.finputType = kSecondGate;
  }	                                                    
}

BOOST_AUTO_TEST_SUITE_END()
