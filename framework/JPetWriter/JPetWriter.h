
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <vector>
#include <string>
#include <TFile.h>
#include <TNamed.h>
#include <TTree.h>
#include <TList.h>
#include "../../JPetLoggerInclude.h"

 #include "../JPetBarrelSlot/JPetBarrelSlot.h"
 #include "../JPetEvent/JPetEvent.h"
 #include "../JPetHit/JPetHit.h"
 #include "../JPetPM/JPetPM.h"
 #include "../JPetScin/JPetScin.h"
 #include "../JPetSigCh/JPetSigCh.h"
 #include "../JPetSignal/JPetSignal.h"
 #include "../JPetTRB/JPetTRB.h"
 #include "../JPetTSlot/JPetTSlot.h"
 #include "../JPetKB/JPetKB.h"


/// @todo what about the copy constructor and the asignment operator

class JPetWriter {
public:
    JPetWriter(const char* file_name);
    virtual ~JPetWriter();
    template <class T>
    bool Write(const T& obj);
    /**
     * @todo Argument prbably should be const, but root method TTree::Branch() used in it is not. How to solve it?
     */
    template <class T>
    bool Write(std::vector<T>& obj);
    
    template <class T>
    bool writeUsingList(const T &p_item, const std::string &p_objectName);
    template <class T>
    bool writeUsingList(std::vector<T> &p_container, const std::string &p_objectName);
    //bool OpenFile(const char* filename);
    void WriteHeader(TObject* header);
    void CloseFile();
    void closeFileUsingList(void);
    
protected:
    std::string fFileName;
    TFile fFile;
    bool fIsBranchCreated;
    TTree fTree;
    TList m_TList;
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
	
	for (int i = 0; i < obj.size(); i++){
        	filler = &obj[i]; 
		fTree.Fill();      
	}
	
	fTree.FlushBaskets();
    
	return true;
}

template <class T>
bool JPetWriter::writeUsingList(const T &p_item, const std::string &p_objectName)
{
  std::vector<T> l_wrapper;
  l_wrapper.push_back(p_item);
  
  return writeUsingList(l_wrapper, p_objectName);
}

template <class T>
bool JPetWriter::writeUsingList(std::vector<T> &p_container, const std::string &p_objectName)
{
  if(p_container.empty())
  {
    WARNING("Vector passed is empty");
    return false;
  }
  if(!fFile.IsOpen())
  {
    ERROR("Could not write to file.");
    return false;
  }
  
  for(typename std::vector<T>::iterator it = p_container.begin(); it != p_container.end(); ++it)
  {
    m_TList.Add(&(*it));
  }

  fFile.WriteObject(&m_TList, p_objectName.c_str());
  
  return true;
}

#endif /*  !JPETWRITER_H */
