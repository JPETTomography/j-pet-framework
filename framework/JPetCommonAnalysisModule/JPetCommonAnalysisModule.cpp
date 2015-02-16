#include "../JPetManager/JPetManager.h"

#include "JPetCommonAnalysisModule.h"
#include "TSystem.h"

ClassImp(JPetCommonAnalysisModule);

/*
JPetCommonAnalysisModule::JPetCommonAnalysisModule():
  JPetAnalysisModule(),
  fEventNb(0)
{
  gSystem->Load("libTree");
}
*/

JPetCommonAnalysisModule::JPetCommonAnalysisModule(const char* name, const char* title,
				       const char * in_file_suffix,
				       const char * out_file_suffix):
  JPetAnalysisModule(name, title),
  fVersion(0),
  fRunNb(0),
  fEventNb(0),
  fEvent(0),
  fWriter(0),
  fReader(0),
  fHeader(0),
  fInFileName(""),
  fOutFileName(""),
  fInFileSuffix(in_file_suffix),
  fOutFileSuffix(out_file_suffix)//,
  //  fParamManager(JPetManager::GetManager().getParamManagerInstance())
{
  gSystem->Load("libTree");
}


JPetCommonAnalysisModule::~JPetCommonAnalysisModule()
{
  if (fWriter != NULL) delete fWriter;
  if (fReader != NULL) delete fReader;
}

void JPetCommonAnalysisModule::createInputObjects(const char* inputFilename)
{
  fInFileName = inputFilename;
  fInFileName += ".";
  fInFileName += fInFileSuffix;
  
  // create the JPetReader and load the tree
  fReader = new JPetReader();
  if ( fReader->openFile( fInFileName.c_str() ) == 0) {
    std::cerr << fName << ": Unable to open the input file. Exiting." << std::cerr;
    exit(-1);
  }
  fReader->readData();
  fEventNb = fReader->getEntries();

  INFO( Form("Starting %s.", GetName() ) );
  
  //fParamManager.readParametersFromFile( fReader );
  JPetManager::GetManager().getParamManagerInstance().readParametersFromFile(fReader);

  // read the header from the previous analysis stage
  fHeader = fReader->getHeaderClone();
  // add info about this module to the processing stages' history in Tree header
  fHeader->addStageInfo( this->GetName(), this->GetTitle(), getVersion(),
			 JPetManager::GetManager().GetTimeString() );

  
 }

 void JPetCommonAnalysisModule::createOutputObjects(const char* outputFilename)
 {
   fOutFileName = outputFilename;
   fOutFileName += ".";
   fOutFileName += fOutFileSuffix;

   fEvent = 0;
   fWriter = new JPetWriter( fOutFileName.c_str() );

   // call user function before starting processing
   begin();
 }


 void JPetCommonAnalysisModule::terminate()
 {
   // call user function before terminating processing
   end();

   INFO( Form("Finished processing %s.", GetName() ) );
   fWriter->writeHeader( fHeader ); 
   fWriter->writeObject( getStatsObjects(), "Stats" );

   // rewrite the parametric objects from input file to output file
   JPetManager::GetManager().getParamManagerInstance().saveParametersToFile(fWriter);
   JPetManager::GetManager().getParamManagerInstance().clearParameters();
   //   fParamManager.saveParametersToFile( fWriter );
   //   fParamManager.clearParameters();  

   fWriter->closeFile();
   fReader->closeFile();

}


const JPetParamBank & JPetCommonAnalysisModule::getParamBank(){
  return JPetManager::GetManager().getParamManagerInstance().getParamBank();
}

