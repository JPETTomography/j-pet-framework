/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetScopeTaskUtils.h
 */

#include "./JPetRecoSignal/JPetRecoSignal.h"

const double ks2ps = 1.0e+12;
const double kV2mV = 1.0e+3;
const int kbuflen = 256;

namespace RecoSignalUtils
{
  JPetRecoSignal generateSignal(const char* filename) {
    FILE* input_file = fopen(filename, "r");
    if (!input_file) {
      ERROR(Form("Error: cannot open file %s", filename));
      return JPetRecoSignal(0);
    }
    int segment_size = 0;
    std::string fileNameWithExtension(filename);
    if(fileNameWithExtension.substr(fileNameWithExtension.find_last_of(".") + 1) != "tsv") {
      char buf[kbuflen];
      char tmp[kbuflen];
      if (fgets(buf, kbuflen, input_file) != 0)
      sscanf(buf, "%s %*s %*s", tmp);
      if (fgets(buf, kbuflen, input_file) != 0)
      sscanf(buf, "%*s %*s %*s %d", &segment_size);
      if (fgets(buf, kbuflen, input_file) != 0);
      if (fgets(buf, kbuflen, input_file) != 0)
      sscanf(buf, "%*s %s %s %*s", tmp, tmp + kbuflen/2);
      if (fgets(buf, kbuflen, input_file) != 0);
    }
    JPetRecoSignal reco_signal(segment_size);
    for (int i = 0; i < segment_size; ++i) {
      float value, threshold;
      int stat;
      stat = fscanf(input_file, "%f %f\n", &value, &threshold);
      if (stat != 2) {
	       ERROR(Form("Non-numerical symbol in file %s at line %d", filename, i + 6));
	       char tmp[kbuflen];
	       if (fgets(tmp, kbuflen, input_file) != 0);
      }
      float time = value * ks2ps;
      float amplitude = threshold * kV2mV;
      reco_signal.setShapePoint(time, amplitude);
    }
    fclose(input_file);
    return reco_signal;
  }
}
