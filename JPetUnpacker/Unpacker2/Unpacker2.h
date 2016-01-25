#ifndef Unpacker2_h
#define Unpacker2_h

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TObjectTable.h>
#include <string>
#include "UnpackingModule.h"
#include <map>

class Unpacker2 : public TObject {
  
private:
  
  map<std::string, UnpackingModule*> unpackers;
  
  int eventsToAnalyze;
  
  size_t reverseHex(size_t n);
  
  bool invertBytes;
  bool fullSetup;
  
  bool debugMode;
  
  int fileSize;

public:
  
  Unpacker2(const char* hldFile, const char* configFile, int numberOfEvents);
  ~Unpacker2() {}
  
  void ParseConfigFile(std::string f, std::string s);
  void DistributeEvents(std::string f);
  
  void AddUnpacker(std::string s, UnpackingModule* u) { unpackers[s] = u; }
  UnpackingModule* GetUnpacker(std::string s) { return unpackers[s]; }
  
  struct EventHdr {
    UInt_t fullSize;
    UInt_t decoding;
    UInt_t id;
    UInt_t seqNr;
    UInt_t date;
    UInt_t time;
    UInt_t runNr;
    UInt_t pad;
  } hdr;
  
  struct SubEventHdr {
    UInt_t size;
    UInt_t decoding;
    UInt_t hubAddress;
    UInt_t trgNr;
  } subHdr;
  
  UInt_t* pHdr; //!
  UInt_t* subPHdr; //!
  
  size_t getSubHdrSize()    const { return sizeof(SubEventHdr); }
  size_t getHdrSize()    const { return sizeof(EventHdr); }
  UInt_t getFullSize()   const { return ((EventHdr*)pHdr)->fullSize; }
  size_t getDataSize();
  std::string getHubAddress();
  size_t getDataLen()    const { return ((getFullSize() - getHdrSize()) + 3) / 4; }
  size_t align8(const size_t i) const { return 8 * size_t((i - 1) / 8 + 1); }
  size_t getPaddedSize() { return align8(getDataSize()); }
  size_t getPaddedEventSize() { return align8(getFullSize()); }
  
  size_t ReverseHex(size_t n);
    
  ClassDef(Unpacker2,1);
  
};



#endif
