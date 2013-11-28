
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

using namespace std;

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
    bool Write(vector<T>& obj);
    //bool OpenFile(const char* filename);
    void CloseFile();
    
protected:
    string fFileName;
    TFile fFile;
};

template <class T>
bool JPetWriter::Write(const T& obj){
    vector<T> wrapper;
    wrapper.push_back(obj);
    Write(wrapper);
}

template <class T>
bool JPetWriter::Write( vector<T>& obj) {
	
    if (obj.size() == 0) {
        WARNING("Vector passed is empty");
        return false;
    }
    
    if ( !fFile.IsOpen() ) {
		ERROR("Could not write to file. Have you closed it already?");
		return false;
	}
    
    fFile.cd(fFileName.c_str()); // -> http://root.cern.ch/drupal/content/current-directory
    
    TTree tree;
	
	T* filler = &obj[0];
    
	tree.Branch(filler->GetName(), filler->GetName(), &filler);
	
	for (int i = 0; i < obj.size(); i++){
        filler = &obj[i]; 
		tree.Fill();      
	}
	
	tree.Write();
    
	return true;
}

#endif /*  !JPETWRITER_H */
