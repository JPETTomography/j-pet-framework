/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetParamGetterAscii.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Class to generate parameter bank based on ASCII file content.
 */ 

#ifndef JPETPARAMGETTERASCII_H 
#define JPETPARAMGETTERASCII_H 

class JPetParamBank;

class JPetParamGetterAscii {
public:
  JPetParamGetterAscii();
  JPetParamBank* generateParamBank(const char* filename ,const int runNumber);

private:
  JPetParamGetterAscii(const JPetParamGetterAscii &DBParamGetter);
  JPetParamGetterAscii& operator=(const JPetParamGetterAscii &DBParamGetter);

private:
  JPetParamBank* loadFileContent(const char* inputFile, int runNumber);

};

#endif /*  !JPETPARAMGETTERASCII_H */
