
#include <iostream>
#include <fstream>
#include <sstream>
#include "./tinyxml2-master/tinyxml2.h"
#include <map>
#include <cstdio>
#include "Unpacker2.h"
#include "Event.h"
#include "ADCHit.h"
#include "TDCHit.h"
#include "UnpackingModule.h"
#include "Unpacker_HPTDC_VHR.h"
#include "Unpacker_HPTDC_HR.h"
#include "Unpacker_HUB2.h"
#include "Unpacker_TRB2.h"
#include "Unpacker_Shower.h"
#include "Unpacker_Ecal_ADC.h"
#include "Unpacker_TRB3.h"
#include "Unpacker_Lattice_TDC.h"


using namespace std;

ClassImp(Unpacker2);

Unpacker2::Unpacker2(const char* hldFile, const char* configFile, int numberOfEvents) {
  
  eventsToAnalyze = numberOfEvents;
  debugMode = false;
  
  invertBytes = false;
  fullSetup = true;
  
  fileSize = 0;
  
  //*** PARSING CONFIG FILE
  ParseConfigFile(string(hldFile), string(configFile));

  //*** READING BINARY DATA AND DISTRIBUTING IT TO APPROPRIATE UNPACKING MODULES
  DistributeEvents(string(hldFile));
}

void Unpacker2::ParseConfigFile(string f, string s) {
  
  // open the data file to check the byte ordering
  ifstream* file = new ifstream(f.c_str());
  
  if (file->is_open()) {

    // skip the file header
    file->ignore(32);
    
    // read out the header of the event into hdr structure
    pHdr = (UInt_t*) &hdr;
    file->read((char *) (pHdr), getHdrSize());
    subPHdr = (UInt_t*) &subHdr;
    file->read((char *) (subPHdr), getSubHdrSize());
    if(((SubEventHdr*)subPHdr)->decoding == 16777728) {
      invertBytes = true;
    }
    
    // find the size of the file
    file->seekg(0, ios::end);
    fileSize = file->tellg();
  }
  file->close();

  
  // parsing xml config file
  tinyxml2::XMLDocument doc;
  doc.LoadFile(s.c_str());
  
  if (doc.ErrorID() != 0) {
   cerr<<"ERROR: failed to open config file"<<endl; 
   exit(0);
  }
  
  
  // get the config options from the config file
  if(doc.FirstChildElement("READOUT")->FirstChildElement("DEBUG") != 0) {
    if (string(doc.FirstChildElement("READOUT")->FirstChildElement("DEBUG")->GetText()) == "ON")
      debugMode = true;
  }
  else {
    cerr<<"ERROR: Incorrect config file structure"<<endl;
    exit(0);
  }     
  
  if (debugMode == true)
    cerr<<"DEBUG mode on"<<endl;
  
  // get the first data source entry in the config file
  tinyxml2::XMLElement* element = doc.FirstChildElement("READOUT")->FirstChildElement("DATA_SOURCE");
  string type;
  string address;
  string hubAddress;
  string correctionFile;
  int channels;
  int offset;
  int resolution;
  int referenceChannel;
  string measurementType;
  UnpackingModule* m;
  tinyxml2::XMLNode* node;
  
  // iterate through entries and create appropriate unpackers
  while(true) {
    // read out values from xml entry
    type = string(element->FirstChildElement("TYPE")->GetText());
    address = string(element->FirstChildElement("TRBNET_ADDRESS")->GetText());
    hubAddress = string(element->FirstChildElement("HUB_ADDRESS")->GetText());
    referenceChannel = atoi(element->FirstChildElement("REFERENCE_CHANNEL")->GetText());
    correctionFile = string(element->FirstChildElement("CORRECTION_FILE")->GetText());
    
    // create appropriate unpacking module
    if (type == "TRB2_S") { // standalone type
	fullSetup = false;
      
	m = new Unpacker_TRB2(type, address, hubAddress, 0, 0, 0, "", invertBytes, debugMode);
	m->SetReferenceChannel(referenceChannel);
	
	// create additional unpackers for internal modules 
	node = element->FirstChildElement("MODULES")->FirstChildElement("MODULE");
	while(true) {
	  
	  if (node == 0)
	    break;
	  
	  type = string(node->ToElement()->FirstChildElement("TYPE")->GetText());
	  address = string(node->ToElement()->FirstChildElement("TRBNET_ADDRESS")->GetText());
	  channels = atoi(node->ToElement()->FirstChildElement("NUMBER_OF_CHANNELS")->GetText());
	  offset = atoi(node->ToElement()->FirstChildElement("CHANNEL_OFFSET")->GetText());
	  resolution = atoi(node->ToElement()->FirstChildElement("RESOLUTION")->GetText());
	  measurementType = string(node->ToElement()->FirstChildElement("MEASUREMENT_TYPE")->GetText());
	  
	  if (type == "HPTDC_HR") {
	    m->AddUnpacker(address, new Unpacker_HPTDC_HR(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	  }
	  else if (type == "HPTDC_VHR") {
	    Unpacker_HPTDC_VHR* u = new Unpacker_HPTDC_VHR(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode);
	    u->SetInlCorrection(node->ToElement()->FirstChildElement("INL_FILE")->GetText());
	    m->AddUnpacker(address, u);
	  }
	  else {
	    m->AddUnpacker(address, new UnpackingModule(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	  }
	  
	  node = node->ToElement()->NextSibling();
	  
	}
	
    }
    else if (type == "HUB2") {
	m = new Unpacker_HUB2(type, address, hubAddress, 0, 0, 0, "", invertBytes, debugMode);
	
	node = element->FirstChildElement("MODULES")->FirstChildElement("MODULE");
	
	while(true) {
	  if (node == 0)
	    break;
	  
	  type = string(node->ToElement()->FirstChildElement("TYPE")->GetText());
	  address = string(node->ToElement()->FirstChildElement("TRBNET_ADDRESS")->GetText());
	  
	  UnpackingModule* t;
	  string tAddr;
	  
	  if (type == "TRB2") {
	    
	    t = new Unpacker_TRB2(type, address, address, 0, 0, 0, "", invertBytes, debugMode);
	    
	    tAddr = address;
	    
	    tinyxml2::XMLNode* internalNode = node->ToElement()->FirstChildElement("MODULES")->FirstChildElement("MODULE");
	    
	    while(true) {
	      
	      if (internalNode == 0)
		break;

	      type = string(internalNode->ToElement()->FirstChildElement("TYPE")->GetText());
	      address = string(internalNode->ToElement()->FirstChildElement("TRBNET_ADDRESS")->GetText());
	      channels = atoi(internalNode->ToElement()->FirstChildElement("NUMBER_OF_CHANNELS")->GetText());
	      offset = atoi(internalNode->ToElement()->FirstChildElement("CHANNEL_OFFSET")->GetText());
	      resolution = atoi(internalNode->ToElement()->FirstChildElement("RESOLUTION")->GetText());
	      measurementType = string(internalNode->ToElement()->FirstChildElement("MEASUREMENT_TYPE")->GetText());
	      
	      if (type == "HPTDC_HR") {
		t->AddUnpacker(address, new Unpacker_HPTDC_HR(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	      }
	      else if (type == "HPTDC_VHR") {
		Unpacker_HPTDC_VHR* u = new Unpacker_HPTDC_VHR(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode);
		u->SetInlCorrection(internalNode->ToElement()->FirstChildElement("INL_FILE")->GetText());
		t->AddUnpacker(address, u);
	      }
	      else {
		t->AddUnpacker(address, new UnpackingModule(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	      }
	      
	      internalNode = internalNode->ToElement()->NextSibling();
	    }
	  }
	  
	  m->AddUnpacker(tAddr, t);
	    
	  node = node->ToElement()->NextSibling();
	}
    }
    else if (type == "SHOWER") {
      m = new Unpacker_Shower(type, address, address, 0, 0, 0, "", invertBytes, debugMode);
      m->debugMode = debugMode;
	    
      tinyxml2::XMLNode* internalNode = node->ToElement()->FirstChildElement("MODULES")->FirstChildElement("MODULE");
	    
      while(true) {
	      
	if (internalNode == 0)
	  break;

	type = string(internalNode->ToElement()->FirstChildElement("TYPE")->GetText());
	address = string(internalNode->ToElement()->FirstChildElement("TRBNET_ADDRESS")->GetText());
	channels = atoi(internalNode->ToElement()->FirstChildElement("NUMBER_OF_CHANNELS")->GetText());
	offset = atoi(internalNode->ToElement()->FirstChildElement("CHANNEL_OFFSET")->GetText());
	resolution = atoi(internalNode->ToElement()->FirstChildElement("RESOLUTION")->GetText());
	measurementType = string(internalNode->ToElement()->FirstChildElement("MEASUREMENT_TYPE")->GetText());
	      
	if (type == "ECAL_ADC") {
	  m->AddUnpacker(address, new Unpacker_Ecal_ADC(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	}
	else {
	  m->AddUnpacker(address, new UnpackingModule(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	}
	      
	internalNode = internalNode->ToElement()->NextSibling();
      }
    }
    else if (type == "TRB3_S") {
      fullSetup = false;

      m = new Unpacker_TRB3(type, address, hubAddress, 0, 0, 0, "", invertBytes, debugMode);
      m->SetReferenceChannel(referenceChannel);

      // create additional unpackers for internal modules 
      node = element->FirstChildElement("MODULES")->FirstChildElement("MODULE");
      while(true) {

	if (node == 0)
	  break;

	type = string(node->ToElement()->FirstChildElement("TYPE")->GetText());
	address = string(node->ToElement()->FirstChildElement("TRBNET_ADDRESS")->GetText());
	channels = atoi(node->ToElement()->FirstChildElement("NUMBER_OF_CHANNELS")->GetText());
	offset = atoi(node->ToElement()->FirstChildElement("CHANNEL_OFFSET")->GetText());
	resolution = atoi(node->ToElement()->FirstChildElement("RESOLUTION")->GetText());
	measurementType = string(node->ToElement()->FirstChildElement("MEASUREMENT_TYPE")->GetText());

	if (type == "LATTICE_TDC") {
	  m->AddUnpacker(address, new Unpacker_Lattice_TDC(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode, correctionFile));
	}
	else {
	  m->AddUnpacker(address, new UnpackingModule(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode));
	}
	
	node = node->ToElement()->NextSibling();
      }      
    }
    else  { // default type
	m = new UnpackingModule(type, address, hubAddress, 0, 0, 0, "", invertBytes, debugMode);
	cerr<<"  -- Creating UnpakingModule for unassigned type"<<endl;
    }
    
    // add the module to the list
    AddUnpacker(hubAddress, m);
    
    // take and check if next one entry exists
    node = element->NextSibling();
    if (node == 0) // if it's the end of config file, exit
      break;
    
    // if there are still some entries, continue
    element = node->ToElement();
  }
}

void Unpacker2::DistributeEvents(string f) {
  ifstream* file = new ifstream(f.c_str());
  
  if (file->is_open()) {

    // skip the file header
    file->ignore(32);
    
    int analyzedEvents = 0;
    
    Event* event = 0;
    
    // open a new file
    string newFileName = f + ".root"; 
    TFile* newFile = new TFile(newFileName.c_str(), "RECREATE");
    TTree* newTree = new TTree("T", "Tree");
    Int_t split = 2;
    Int_t bsize = 64000;
    newTree->Branch("event", "Event", &event, bsize, split);
    
    cerr<<"Starting event loop"<<endl;
    
    event = new Event();
    
    // iterate through all the events in the file
    while(true) {
    
      // read out the header of the event into hdr structure
      pHdr = (UInt_t*) &hdr;
      file->read((char *) (pHdr), getHdrSize());
      
      size_t eventSize = (size_t) getFullSize();
            
      if(debugMode == true)
	cerr<<"Unpacker2.cc: Starting new event analysis, going over subevents"<<endl;
      
      while(true) {
	subPHdr = (UInt_t*) &subHdr;
	file->read((char *) (subPHdr), getSubHdrSize());
	
	// read out the entire data of the event
	UInt_t* pData = new UInt_t[getDataSize()];
	file->read((char*) (pData), getDataSize());
	
	if(debugMode == true) {
	  cerr<<"Unpacker2.cc: Subevent data size: "<<getDataSize()<<" starting with ";
	  printf("%08X\n", (*pData));
	  cerr<<"Unpacker2.cc: Subevent details: "<<((SubEventHdr*)subPHdr)->decoding<<" "<<((SubEventHdr*)subPHdr)->hubAddress<<" "<<((SubEventHdr*)subPHdr)->trgNr<<endl;
	}
	
	// call the unpacking module
	UnpackingModule* u = GetUnpacker(getHubAddress());
	if (u != NULL && (*pData) != 0) {
	  if(debugMode == true)
	    cerr<<"Unpacker2.cc: Processing event "<<analyzedEvents<<" on "<<getHubAddress()<<endl;
	  GetUnpacker(getHubAddress())->SetEntireEventSize(getDataSize());
	  GetUnpacker(getHubAddress())->ProcessEvent(pData, event);
	  
	  // gather decoded hits and fill them into event
	
	  GetUnpacker(getHubAddress())->GetTDCHits();
	  GetUnpacker(getHubAddress())->GetADCHits();
	
	}
	else if((*pData) == 0) {
	  cerr<<"WARNING: First data word empty, skipping event nr "<<analyzedEvents<<endl;
	}
	else if(u == NULL) {
	  cerr<<"ERROR: Unpacker not found for address: "<<getHubAddress()<<endl;
	  exit(1);
	}

	if(debugMode == true)
	  cerr<<"Unpacker2.cc: Ignoring "<<(getPaddedSize() - getDataSize())<<" bytes and reducing eventSize by "<<getDataSize(); 
	
	delete pData;
	
	// remove the padding bytes
	file->ignore(getPaddedSize() - getDataSize());
	
	eventSize -= getDataSize();
	
	if(debugMode == true)
	  cerr<<" leaving eventSize of "<<eventSize<<endl;
	
	if(eventSize == 48 && fullSetup == false) { break; }
	
	eventSize -= getPaddedSize() - getDataSize();
	
	if(eventSize == 64 && fullSetup == true) { break; }
      }
    
      
      newTree->Fill();
      
      if(analyzedEvents % 10000 == 0) {
	cerr<<analyzedEvents<<endl;
	//gObjectTable->Print();
      }
      
      analyzedEvents++;
      
      event->Clear();
      
      if(debugMode == true) {
	cerr<<"Unpacker2.cc: Ignoring padding of the event "<<(align8(eventSize) - eventSize)<<endl;
	cerr<<"Unpacker2.cc: File pointer at "<<file->tellg()<<" of "<<fileSize<<" bytes"<<endl;
      }
      file->ignore(align8(eventSize) - eventSize);
      
      // check the end of loop conditions
      if(fileSize - file->tellg() < 40) { break; }
      if((file->eof() == true) || ((int)file->tellg() == fileSize)) { break; }
      if(analyzedEvents == eventsToAnalyze) { break; }
    }

    newFile->Write();
    
    delete newTree;
  }
  else { cerr<<"ERROR:failed to open data file"<<endl; }
  
  file->close();

  //*** END OF READING BINARY DATA
}

size_t Unpacker2::getDataSize() {
  if (invertBytes == false) {
    return (size_t) (((SubEventHdr*)subPHdr)->size - 16);
  }
  else {
    return (size_t) (ReverseHex(((SubEventHdr*)subPHdr)->size) - 16);
  }
  
  return -1;
}

std::string Unpacker2::getHubAddress() {
  string s = "0000";
  stringstream sstream;
  if (invertBytes == false) {
    sstream<<hex<<((SubEventHdr*)subPHdr)->hubAddress;  
  }
  else {
    sstream<<hex<<ReverseHex((UInt_t)((SubEventHdr*)subPHdr)->hubAddress);  
  }
  
  s = s.replace(4 - sstream.str().length(), sstream.str().length(), sstream.str());
  
  return s;
}

size_t Unpacker2::ReverseHex(size_t n) {
  size_t a, b, c, d, e;
  a = n & 0x000000ff;
  b = n & 0x0000ff00;
  c = n & 0x00ff0000;
  d = n & 0xff000000;
  
  a <<= 24;
  b <<= 8;
  c >>= 8;
  d >>=24 ;
  
  e = a|b|c|d;
  
  return e;
}
