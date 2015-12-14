/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetParamGetterAscii.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Class to generate parameter bank based on ASCII file content.
 */ 

#ifndef JPETPARAMGETTERASCII_H 
#define JPETPARAMGETTERASCII_H 

#include "../JPetParamBank/JPetParamBank.h"

class JPetParamGetterAscii : public JPetParamGetter {
public:
  JPetParamGetterAscii(const char* filename) : filename(filename) {}
  JPetParamBank* generateParamBank(const int runNumber);

private:
  JPetParamGetterAscii(const JPetParamGetterAscii &DBParamGetter);
  JPetParamGetterAscii& operator=(const JPetParamGetterAscii &DBParamGetter);

private:
  JPetParamBank* loadFileContent(int runNumber);

  std::string filename;

};

#endif /*  !JPETPARAMGETTERASCII_H */
