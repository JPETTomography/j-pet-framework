#include "./ModuleA.h"
#include "JPetManager/JPetManager.h"

ClassImp(ModuleA);

ModuleA::ModuleA(const char* name, const char* title,
                 const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
}

ModuleA::~ModuleA() {
  setVersion(MODULE_VERSION);
  if (fHLDReader != NULL) delete fHLDReader;
}

void ModuleA::createInputObjects(const char* inputFilename) {
  INFO(Form("Starting %s.", GetName()));

  fInFileName = inputFilename;
  fInFileName += ".";
  fInFileName += fInFileSuffix;

  // create HLD Reader and load the tree
  fHLDReader = new JPetHLDReader();
  if (!fHLDReader->openFileAndLoadData(fInFileName.c_str())) {
    ERROR("Unable to open file");
    exit(-1);
  }
  fEventNb = fHLDReader->getNbOfAllEvents();

  // create a header to be stored along with the output tree
  fHeader = new JPetTreeHeader(JPetManager::GetManager().getRunNumber());

  // add general info to the Tree header
  fHeader->setBaseFileName(
      JPetManager::GetManager().getInputFileNames()[0].c_str());

  // add info about this module to the processing stages' history in Tree header
  fHeader->addStageInfo(this->GetName(), this->GetTitle(), MODULE_VERSION,
                        JPetManager::GetManager().GetTimeString());

}

void ModuleA::begin() {
}

void ModuleA::exec() {
  // Get HLD Event
  fHLDReader->nthEvent(fEvent);
  Event* evt = (Event*) (&(fHLDReader->getCurrentEvent()));
  

  // get number of TDC hits in a HLD event
  int ntdc = evt->GetTotalNTDCHits();

  JPetTimeWindow tslot;
  tslot.setIndex(fEvent);

  TClonesArray* tdcHits = evt->GetTDCHitsArray();

  // iterate over TDC hits
  TDCHit* tdchit;
  for (int i = 0; i < ntdc; i++) {

    tdchit = (TDCHit*) tdcHits->At(i);
    JPetSigCh sigChTmp;

    // get data channel number which corresponds to the TOMB Channel number
    unsigned int tomb_number =  tdchit->GetChannel();

    if (tomb_number % 65 == 0) { // skip trigger signals from TRB
      continue;
    }

    // find index of corresponding TOMB Channel
    int tombch_index = 0;
    while (tombch_index < getParamBank().getTOMBChannelsSize()
	   && getParamBank().getTOMBChannel(tombch_index).getChannel()
	   != tomb_number)
      tombch_index++;
    if (tombch_index == getParamBank().getTOMBChannelsSize()) { // TOMBChannel object not found
      WARNING( Form("TOMB Channel for DAQ channel %d was not found in database! Ignoring this channel.", tomb_number) );
      continue;
    }
    // get TOMBChannel object from database
    JPetTOMBChannel & tomb_channel = getParamBank().getTOMBChannel(tombch_index);
    
    sigChTmp.setDAQch(tomb_number);

    if (tomb_channel.getLocalChannelNumber() % 2 == 1) { // leading edge
      sigChTmp.setType(JPetSigCh::Leading);
      //set the local threshold number(1...4) using local channel number (1...8)
      sigChTmp.setThresholdNumber(
          (tomb_channel.getLocalChannelNumber() + 1) / 2.);
    } else {  // trailing edge
      sigChTmp.setType(JPetSigCh::Trailing);
      //set the local threshold number(1...4) using local channel number (1...8)
      sigChTmp.setThresholdNumber(
          tomb_channel.getLocalChannelNumber() / 2.);
    }

    // store pointers to the related parametric objects
    sigChTmp.setPM(tomb_channel.getPM());
    sigChTmp.setFEB(tomb_channel.getFEB());
    sigChTmp.setTRB(tomb_channel.getTRB());
    sigChTmp.setTOMBChannel(tomb_channel);
    
    sigChTmp.setThreshold(tomb_channel.getThreshold());

    // finally, set the time in ps
    sigChTmp.setValue(tdchit->GetLeadTime1() * 10.);
    // and add the sigCh to TSlot
    tslot.addCh(sigChTmp);

  }

  fWriter->write(tslot);

  fEvent++;
}

void ModuleA::end() {
}

void ModuleA::terminate() {
  // cal user function before terminating processing
  end();

  INFO(Form("Finished processing %s.", GetName()));
  fWriter->writeHeader(fHeader);

  // store the parametric objects in the ouptut ROOT file                               

  //  fParamManager.saveParametersToFile( fOutFileName.Data() );
  //  fParamManager.clearParameters();
  getParamManager().saveParametersToFile(
      fWriter);
  getParamManager().clearParameters();

  fWriter->closeFile();
  fHLDReader->closeFile();

}
