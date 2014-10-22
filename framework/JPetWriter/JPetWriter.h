
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
#include "../JPetTOMB/JPetTOMB.h"


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
  void WriteHeader(TObject* header);
  void CloseFile();
  
  template <class T>
  bool write(const T &p_item, const std::string &p_objectName);
  template <class T>
  bool write(std::vector<T> &p_container, const std::string &p_objectName);

  int WriteObject(const TObject* obj, const char* name){ return fFile.WriteObject(obj, name); }
  
  virtual void closeTFile(void);
  
protected:
  std::string fFileName;
  TFile fFile;
  bool fIsBranchCreated;
  TTree fTree;
  
  TFile fTFile;
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

template <class T>
bool JPetWriter::write(const T &p_item, const std::string &p_objectName)
{
  std::vector<T> l_wrapper;
  l_wrapper.push_back(p_item);
  
  return write(l_wrapper, p_objectName);
}

template <class T>
bool JPetWriter::write(std::vector<T> &p_container, const std::string &p_objectName)
{
  if(p_container.empty())
  {
    WARNING("Vector passed is empty");
    return false;
  }
  
  if(!fTFile.IsOpen())
  {
    ERROR("Could not write to file.");
    return false;
  }
  
  for(typename std::vector<T>::iterator it = p_container.begin(); it != p_container.end(); ++it)
  {
    fTList.Add(&(*it));
  }

  fTFile.WriteObject(&fTList, p_objectName.c_str());
  
  return true;
}

#endif	// JPETWRITER_H
