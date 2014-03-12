
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <vector>
#include <string>
#include <TFile.h>
#include <TNamed.h>
#include <TTree.h>
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
    //bool OpenFile(const char* filename);
    void WriteHeader(TObject* header);
    void CloseFile();
    
protected:
    std::string fFileName;
    TFile fFile;
    bool fIsBranchCreated;
    TTree fTree;
};

template <class T>
bool JPetWriter::Write(const T& obj){
    std::vector<T> wrapper;
    wrapper.push_back(obj);
    Write(wrapper);
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

#endif /*  !JPETWRITER_H */
