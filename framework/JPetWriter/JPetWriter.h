
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <string>
#include <TFile.h>
#include <TNamed.h>

class JPetWriter {
public:
    JPetWriter(){}
    virtual ~JPetWriter(){}
   // virtual bool Write(const TNamed& data)=0;
    virtual bool OpenFile(const char* filename);
    virtual void CloseFile();
protected:
    static TFile *fFile;
};
#endif /*  !JPETWRITER_H */
