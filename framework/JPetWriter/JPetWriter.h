
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <vector>
#include <string>
#include <TFile.h>
#include <TNamed.h>
#include <TTree.h>
#include "../../JPetLoggerInclude.h"

using namespace std;

class JPetWriter {
public:
    JPetWriter(const char* file_name);
    virtual ~JPetWriter();
    bool Write(const TNamed& obj);
    /**
     * @todo Argument prbably should be const, but root method TTree::Branch() used in it is not. How to solve it?
     */
    bool Write(vector<TNamed>& obj);
    //bool OpenFile(const char* filename);
    void CloseFile();
    
protected:
    string fFileName;
    TFile fFile;
};
#endif /*  !JPETWRITER_H */
