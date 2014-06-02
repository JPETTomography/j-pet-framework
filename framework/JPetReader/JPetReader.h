// JPetReader.h - Reader
#ifndef JPETREADER_H 
#define JPETREADER_H 

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <boost/noncopyable.hpp>

#include "../JPetScin/JPetScin.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetKB/JPetKB.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetTOMB/JPetTOMB.h"

#include "../../JPetLoggerInclude.h"

// czesc kodu nie jest moja - trzeba poprawic
class JPetReader : private boost::noncopyable
{
public:
  JPetReader(void);
  explicit JPetReader(const char* p_filename);
  virtual ~JPetReader(void);
  
  virtual void CloseFile();
  virtual long long GetEntries () const { return fTree->GetEntries(); }
  virtual int GetEntry (int entryNo) {return fTree->GetEntry(entryNo); } /// the name of the function is bad but it mimics ROOT function 
  virtual bool OpenFile(const char* filename);
  virtual void ReadData(const char* objname = "");
  virtual TNamed& GetData () {return *fObject;}
  TObject* GetHeader();
  
  template <class T>
  void fillContainer(std::vector<T> &p_container, const std::string &p_objectName);
  virtual void closeTFile(void);
  //TFile& getTFile() { return fTFile; }
  
protected:
  TBranch* fBranch;
  TNamed* fObject;
  TTree* fTree;
  TFile* fFile;
  
  TFile fTFile;
};


template <class T>
void JPetReader::fillContainer(std::vector<T> &p_container, const std::string &p_objectName)
{
  TList *l_TList = (TList*)fTFile.Get(p_objectName.c_str());
  
  TObject *l_obj;
  
  TIter next(l_TList);
  while(l_obj = next())
  {
    T *l_item = static_cast<T*>(l_obj);
    p_container.push_back(*l_item);
  }
}

#endif	// JPETREADER_H
