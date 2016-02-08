#include "Unpacker_Lattice_TDC.h"
#include <iostream>

using namespace std;

//ClassImp(Unpacker_Lattice_TDC);

Unpacker_Lattice_TDC::Unpacker_Lattice_TDC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg, string cF) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  
  channelNumber = cN;
  offset = o;
  errorBits = 0;


  leadMult = new int[channelNumber];
	leadFineTimes = new int*[channelNumber]; 
	leadCoarseTimes = new int*[channelNumber];
	leadEpochs = new int*[channelNumber];
  
  trailMult = new int[channelNumber];
	trailFineTimes = new int*[channelNumber]; 
	trailCoarseTimes = new int*[channelNumber];
	trailEpochs = new int*[channelNumber];
 
  for(int i = 0; i < channelNumber; i++) {
		leadMult[i] = 0;
		leadFineTimes[i] = new int[MAX_HITS]; 
		leadCoarseTimes[i] = new int[MAX_HITS];
		leadEpochs[i] = new int[MAX_HITS];
		
		trailMult[i] = 0;
		trailFineTimes[i] = new int[MAX_HITS]; 
		trailCoarseTimes[i] = new int[MAX_HITS];
		trailEpochs[i] = new int[MAX_HITS];
  }
  
	actualEpoch = -100000;

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
    delete [] corrections[i];

		delete [] leadFineTimes[i];
		delete [] leadCoarseTimes[i];
		delete [] leadEpochs[i];
		
		delete [] trailFineTimes[i];
		delete [] trailCoarseTimes[i];
		delete [] trailEpochs[i];
  }
  
  delete [] leadMult;
  delete [] trailMult;

	delete [] leadFineTimes;
	delete [] leadCoarseTimes;
	delete [] leadEpochs;

	delete [] trailFineTimes;
	delete [] trailCoarseTimes;
	delete [] trailEpochs;

  delete [] corrections;
}

void Unpacker_Lattice_TDC::Clear() {
  for(int i = 0; i < channelNumber; i++) {
		delete [] leadFineTimes[i];
		delete [] leadCoarseTimes[i];
		delete [] leadEpochs[i];
		
		delete [] trailFineTimes[i];
		delete [] trailCoarseTimes[i];
		delete [] trailEpochs[i];
    
		leadMult[i] = 0;
		leadFineTimes[i] = new int[MAX_HITS]; 
		leadCoarseTimes[i] = new int[MAX_HITS];
		leadEpochs[i] = new int[MAX_HITS];
		
		trailMult[i] = 0;
		trailFineTimes[i] = new int[MAX_HITS]; 
		trailCoarseTimes[i] = new int[MAX_HITS];
		trailEpochs[i] = new int[MAX_HITS];
  }

	actualEpoch = -100000;
  
}

void Unpacker_Lattice_TDC::ProcessEvent(UInt_t* data) {  
  
  size_t dataSize = GetEntireEventSize();
  
//  if(debugMode == true)
//    cerr<<"Lattice_TDC: received "<<dataSize<<" bytes to unpack"<<endl;
  
  while(dataSize > 0) {
    
    UInt_t data_i = 0;
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }
    
    int header = (data_i >> 29);
    int channel;
    int coarse;
    int fine;
    int epoch;
    
/*    if ((data_i >> 29) == 1) {
      errorBits = data_i & 0xffff;
    }
    else {*/
    
      switch (header) {

/*	case 1:
		errorBits = data_i & 0xffff;
		if(debugMode == true) {
	    printf("%08X\n", data_i);
			cerr<<"Lattice_TDC: TDC Header found"<<endl;
		}
		break;*/
	
	case 3: // epoch ctr
		epoch = data_i & 0xfffffff;
//		if(debugMode == true) {
//	    printf("%08X\n", data_i);
//			cerr<<"Lattice_TDC: EpochCounter found with value "<<epoch<<" assigned as actualEpoch"<<endl;
//		}
		actualEpoch = epoch;
		break;
		

	case 4:// time data
	  channel = (data_i >> 22) & 0x7f;
	  coarse = (data_i & 0x7ff);
	  fine = (data_i >> 12) & 0x3ff;
	  
	  /*if (useCorrections == true) {
	    time = (coarse * 5000. - (corrections[channel]->GetBinContent(fine))) / 10.;
	    fineTimes[channel][leadMult[channel]] = corrections[channel]->GetBinContent(fine) / 10.;
	  }
	  else {
	    time = (coarse*5.-((5.*fine)/469.))*100.;
	    fineTimes[channel][leadMult[channel]] = fine;
	  }*/

	  if (((data_i >> 11) & 0x1) == 1) { // rising edge
//	    if(debugMode == true) {
//	      printf("%08X\n", data_i);
//	      cerr<<"Lattice_TDC: LeadTime found on channel "<<channel<<" with fine "<<fine<<" coarse "<<coarse<<endl; 
//				cerr<<"matched with actualEpoch counter with value "<<actualEpoch<<endl;	      
//	    }

			if (fine != 0x3ff) {
				if (useCorrections == true)
					leadFineTimes[channel][leadMult[channel]] = (corrections[channel]->GetBinContent(fine + 1));
				else		
					leadFineTimes[channel][leadMult[channel]] = fine * 10.0;

				leadCoarseTimes[channel][leadMult[channel]] = coarse;
				leadEpochs[channel][leadMult[channel]] = actualEpoch;
			  leadMult[channel]++;
			}
	  }
	  else { // falling edge	    
//			if(debugMode == true) {
//	      printf("%08X\n", data_i);
//	      cerr<<"Lattice_TDC: TrailTime found on channel "<<channel<<" with fine "<<fine<<" coarse "<<coarse<<endl; 
//				cerr<<"matched with actualEpoch counter with value "<<actualEpoch<<endl;
//	    }

			if (fine != 0x3ff) {
				if (useCorrections == true)
					trailFineTimes[channel][trailMult[channel]] = (corrections[channel]->GetBinContent(fine + 1));
				else		
					trailFineTimes[channel][trailMult[channel]] = fine * 10.0;
				trailCoarseTimes[channel][trailMult[channel]] = coarse;
				trailEpochs[channel][trailMult[channel]] = actualEpoch;
			  trailMult[channel]++;
			}
	  }
	  break;

/*	case 2: // debug word
		if(debugMode == true) {
	    printf("%08X\n", data_i);
			cerr<<"Lattice_TDC: Debug word found"<<endl;
		}
		break;*/
	  
	default:
	  break;
	
     
    }
    
    data++;
    dataSize--;
  }
}

void Unpacker_Lattice_TDC::ProcessEvent(UInt_t* /* data */, Event* /* evt */) { }
