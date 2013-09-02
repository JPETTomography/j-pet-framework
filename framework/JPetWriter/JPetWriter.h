
#ifndef JPETWRITER_H 
#define JPETWRITER_H 

#include <string>

class JPetWriter {
public:
    JPetWriter();
    virtual ~JPetWriter();
    virtual void OpenFile(const char* filename) = 0;
    virtual void CloseFile() = 0;
};
#endif /*  !JPETWRITER_H */