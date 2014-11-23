
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <vector>
#include <string>
#include <TFile.h>
#include <TList.h>
#include <TTree.h>

#ifndef __CINT__
#include <boost/noncopyable.hpp>
#else
namespace boost;
class boost::noncopyable;
#endif /* __CINT __ */

#include "../../JPetLoggerInclude.h"

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetEvent/JPetEvent.h"
#include "../JPetHit/JPetHit.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetTSlot/JPetTSlot.h"

#include "../JPetScin/JPetScin.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetTRB/JPetTRB.h"


/**
 * @brief A class responsible for writing any data to ROOT trees.
 *
 * All objects inheriting from JPetAnalysisModule should use this class in order to access and write to ROOT files.
 */
class JPetWriter : private boost::noncopyable
{
public:
  JPetWriter(const char *p_fileName);
  virtual ~JPetWriter(void);

  template <class T>
  bool Write(const T& obj);
  template <class T>
  bool Write(std::vector<T>& obj);
  //bool OpenFile(const char* filename);
  virtual bool isOpen() const {return fFile.IsOpen(); }
  void WriteHeader(TObject* header);
  void CloseFile();

  int WriteObject(const TObject* obj, const char* name){ return fFile.WriteObject(obj, name); }
  
  
protected:
  std::string fFileName;
  TFile fFile;
  bool fIsBranchCreated;
  TTree fTree;
  
  TList fTList;
};

template <class T>
bool JPetWriter::Write(const T& obj){
    std::vector<T> wrapper;
    wrapper.push_back(obj);
    return Write(wrapper);
}

template <class T>
bool JPetWriter::Write( std::vector<T>& obj) {
	
    if (obj.size() == 0) {
        WARNING("Vector passed is empty");
        return false;
    }
    
    if ( !fFile.IsOpen() ) {
		ERROR("Could not write to file. Have you closed it already?");
		return false;
	}
    
    fFile.cd(/*fFileName.c_str()*/); // -> http://root.cern.ch/drupal/content/current-directory
	
	T* filler = &obj[0];
    
	if(!fIsBranchCreated) {
	  fTree.Branch(filler->GetName(), filler->GetName(), &filler);
	  fIsBranchCreated = true;
	}
	
	for (unsigned int i = 0; i < obj.size(); i++){
        	filler = &obj[i]; 
		fTree.Fill();      
	}
	
	fTree.FlushBaskets();
    
	return true;
}

#endif	// JPETWRITER_H
