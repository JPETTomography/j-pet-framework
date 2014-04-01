// File: inlCorrector.h 
//  
// Author: Wojciech Krzemien <wojciech.krzemien@if.uj.edu.pl> 20.06.2012
// modified: 02.08.2012
#ifndef INLCORRECTOR_H
#define INLCORRECTOR_H
#include <cassert>
#include <iostream>
#include <fstream>

class InlCorrector  {
 public:
  explicit InlCorrector(bool VHResMode = true, const char* filename="correctionParametersVH"): isVHResolutionMode(VHResMode) {
    readParameterFileVH(filename);
  }
  int getCorrectedValue(int channel, int time) {
    int correctedTime = 0;
    int ending = 0; 
    float correction = 0;
    if (isVHResolutionMode) {
      ending = (time & 0x03ff); // last 10 bits
    // array is from 0 to 1023 we must shift the index
      correction = inlCorrectionMatrixVH[channel][ending-1]; 
            ending = static_cast<int>((correction > 0 ) ? correction + 0.5 :correction -0.5); 
            correctedTime = ((time & 0xfffffc00) | ending);
      //correctedTime = (time & 0xfffffc00) + correction;
    } else {
      ending = (time & 0xff);
    // array is from 0 to 255 we must shift the index
      correction = inlCorrectionMatrix[channel][ending-1]; 
      ending = static_cast<int>((correction > 0 ) ? correction + 0.5 :correction -0.5); 
      correctedTime = ((time & 0xffffff00) | ending);
    }
    return correctedTime;
  }
private:
  void readParameterFileVH(const char* filename="correctionParametersVH") {
    int channel = -100;
    std::ifstream file(filename);
    if (!file) {
      std::cerr << "Error opening file " << filename << std::endl;
      return;
    }
    while (file.good()) {
      file >> channel;
      for (int k = 0; k < kNumOfBitsVH; k++) {
        file >> inlCorrectionMatrixVH[channel][k] ;
      } 
    }
  }
  static const int kNumOfBits = 256;
  static const int kNumOfBitsVH = 1024; // for very high resolution mode
  static const int kNumOfChannels = 128;
  static const int kNumOfChannelsVH = 32; // for very high resolution mode
  float inlCorrectionMatrix [kNumOfChannels][kNumOfBits];
  float inlCorrectionMatrixVH [kNumOfChannelsVH][kNumOfBitsVH]; // for very high resolution mode
  bool isVHResolutionMode;
};

#endif 

