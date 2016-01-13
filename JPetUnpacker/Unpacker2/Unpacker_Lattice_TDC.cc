#include "Unpacker_Lattice_TDC.h"
#include <iostream>

using namespace std;

ClassImp(Unpacker_Lattice_TDC);

Unpacker_Lattice_TDC::Unpacker_Lattice_TDC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg, string cF) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  
  channelNumber = cN;
  offset = o;
  errorBits = 0;
  
  leadTimes = new float*[channelNumber];
  trailTimes = new float*[channelNumber];
  leadMult = new UInt_t[channelNumber];
  trailMult = new UInt_t[channelNumber];
  
  fineTimes = new float*[channelNumber];
  coarseTimes = new float*[channelNumber];
 
  for(int i = 0; i < channelNumber; i++) {
    leadTimes[i] = new float[128];
    trailTimes[i] = new float[128];
    leadMult[i] = 0;
    trailMult[i] = 0;
    fineTimes[i] = new float[128];
    coarseTimes[i] = new float[128];
  }
  
  corrections = new TH1F*[cN];
  TFile* file = new TFile();
  ifstream my_file(cF.c_str());
  
  if (cF == "raw") {
    cerr<<"Lattice_TDC: WARNING: No corrections applied"<<endl;
    useCorrections = false;
  }
  else {
    useCorrections = true;
    
    if ((cF == "none") || (cF.find(".root") == string::npos)) {
      cerr<<"Lattice_TDC: WARNING: Linear correction applied"<<endl;
      file = new TFile("./linearCorrection.root", "READ");
    }
    else if (!my_file.good()) {
      cerr<<"Lattice_TDC: WARNING: Linear correction applied - file not found"<<endl; 
      file = new TFile("linearCorrection.root", "READ");
    }
    else {
      cerr<<"Lattice_TDC: WARNING: Calculated corrections applied"<<endl; 
      file = new TFile(cF.c_str(), "READ");
    }
    
    TDirectory* dir = gDirectory->GetDirectory("Rint:/");
    
    for (int i = 0; i < cN; i++){
      TH1F* tmp;
      tmp = (TH1F*)file->Get(Form("correction%d", o + i));
      corrections[i] = (TH1F*)(tmp->Clone(Form("correction%d", o + i)));
      corrections[i]->SetDirectory(dir);
    }
    file->Close();
  }
  
  cerr<<"Lattice_TDC: Creating Unpacker_Lattice_TDC for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<" number of channels "<<channelNumber<<endl;
}

Unpacker_Lattice_TDC::~Unpacker_Lattice_TDC() {
  for(int i = 0; i < channelNumber; i++) {
    delete [] leadTimes[i];
    delete [] trailTimes[i];
    delete [] fineTimes[i];
    delete [] coarseTimes[i];
    delete corrections[i];
  }
  
  delete [] leadMult;
  delete [] trailMult;
  delete [] leadTimes;
  delete [] trailTimes;
  delete [] fineTimes;
  delete [] coarseTimes;
  delete [] corrections;
}

void Unpacker_Lattice_TDC::Clear() {
  for(int i = 0; i < channelNumber; i++) {
    delete [] leadTimes[i];
    delete [] trailTimes[i];
    delete [] fineTimes[i];
    delete [] coarseTimes[i];
    
    leadTimes[i] = new float[128];
    trailTimes[i] = new float[128];
    fineTimes[i] = new float[128];
    coarseTimes[i] = new float[128];
    
    leadMult[i] = 0;
    trailMult[i] = 0;
  }
  
}

void Unpacker_Lattice_TDC::ProcessEvent(UInt_t* data) {  
  
  size_t dataSize = GetEntireEventSize();
  
  if(debugMode == true)
    cerr<<"Lattice_TDC: received "<<dataSize<<" bytes to unpack"<<endl;
  
  while(dataSize > 0) {
    
    UInt_t data_i = 0;
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }
    
    UInt_t header = (data_i >> 31);
    UInt_t channel;
    double time;
    double coarse;
    UInt_t fine;
    
    if ((data_i >> 29) == 1) {
      errorBits = data_i & 0xffff;
    }
    else {
    
      switch (header) {
	
	case 1:
	  channel = (data_i >> 22) & 0x7f;
	  coarse = (data_i & 0x7ff);
	  fine = (data_i >> 12) & 0x3ff;
  //	if (channel == 1) cerr<<"fine: "<<fine<<" coarse: "<<coarse<<endl;
	  //time = (coarse*5.-((5.*fine)/469.))*100.;//coarse*469 - fine - 31; // * (5000.0 / (500.0 - 31.0)); //(coarse * 510) - (fine); //((float)coarse * 5) - ((float)fine / 540); //(coarse << 10) | fine;
	  
	  if (useCorrections == true) {
	    time = (coarse * 5000. - (corrections[channel]->GetBinContent(fine))) / 10.;
	    fineTimes[channel][leadMult[channel]] = corrections[channel]->GetBinContent(fine) / 10.;
	  }
	  else {
	    time = (coarse*5.-((5.*fine)/469.))*100.;
	    fineTimes[channel][leadMult[channel]] = fine;
	  }
	  
	  coarseTimes[channel][leadMult[channel]] = coarse;
	  
	  if (((data_i >> 11) & 0x1) == 1) { // rising edge
	    leadTimes[channel][leadMult[channel]] = time;
	    if(debugMode == true) {
	      printf("%08X\n", data_i);
	      cerr<<"Lattice_TDC: LeadTime found on channel "<<channel<<" with value "<<time<<endl; 
	      
	      cerr<<"coarse: "<<coarse<<" fine: "<<fine<<" time: "<<time<<endl;
	      
	    }
	    leadMult[channel]++;
	  }
	  else { // falling edge
	    trailTimes[channel][trailMult[channel]] = time;
	    //cerr<<"processD channel="<<channel<<" fine = "<<fine<<endl;
	    if(debugMode == true) {
	      printf("%08X\n", data_i);
	      cerr<<"Lattice_TDC: TrailTime found on channel "<<channel<<" with value "<<time<<endl;
	    }
	    trailMult[channel]++;
	  }
	  break;
	  
	default:
	  break;
	
      }
    }
    
    data++;
    dataSize--;
  }
}

void Unpacker_Lattice_TDC::ProcessEvent(UInt_t* data, Event* evt) { }
