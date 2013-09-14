
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <string>
#include <TNamed.h>

class JPetWriter {
public:
    JPetWriter();
    virtual ~JPetWriter();
    virtual bool Write(const TNamed& data) = 0;
    virtual void OpenFile(const char* filename) = 0;
    virtual void CloseFile() = 0;
};
#endif /*  !JPETWRITER_H */