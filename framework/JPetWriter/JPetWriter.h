
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
    JPetWriter(){}
    virtual ~JPetWriter(){}
    bool Write(const vector<TNamed>& obj, const char* file_name);
    virtual bool OpenFile(const char* filename);
    virtual void CloseFile();
protected:
    static TFile *fFile;
};
#endif /*  !JPETWRITER_H */
