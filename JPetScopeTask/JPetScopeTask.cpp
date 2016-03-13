#include "../JPetScopeTask/JPetScopeTask.h"
#include "../JPetParamManager/JPetParamManager.h"

#include <iostream>
#include <string>
#include "JPetScopeTaskUtils.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;
/*
const double ks2ps = 1.0e+12;
const double kV2mV = 1.0e+3;
const int kbuflen = 256;



JPetRecoSignal generateSignal(const char* filename) {
  
  // Open File
  
  FILE* input_file = fopen(filename, "r");

  if (!input_file) {
    ERROR(Form("Error: cannot open file %s", filename));
    return JPetRecoSignal(0);
  }
  
  // Read Header

  int segment_size = 0;
  
  std::string fileNameWithExtension(filename);
  if(fileNameWithExtension.substr(fileNameWithExtension.find_last_of(".") + 1) != "tsv")
  {
    char buf[kbuflen];
    char tmp[kbuflen];

    if (fgets(buf, kbuflen, input_file) != 0)
    sscanf(buf, "%s %*s %*s", tmp);

    //fScopeType = tmp;

    if (fgets(buf, kbuflen, input_file) != 0)
    sscanf(buf, "%*s %*s %*s %d", &segment_size);

    if (fgets(buf, kbuflen, input_file) != 0);
    //sscanf(buf, "%*s %*s %*s");

    if (fgets(buf, kbuflen, input_file) != 0)
    sscanf(buf, "%*s %s %s %*s", tmp, tmp + kbuflen/2);

    //fDate = tmp;
    //fTime = tmp + kbuflen/2;

    if (fgets(buf, kbuflen, input_file) != 0);
    //sscanf(buf, "%*s %*s");
  }

  // Read Data

  JPetRecoSignal reco_signal(segment_size);

  for (int i = 0; i < segment_size; ++i) {
  
    float value, threshold;
    int stat;
 
    if(value >= 0.f && threshold >= 0.f)
    {
      stat = fscanf(input_file, "%f %f\n", &value, &threshold);

      if (stat != 2) {
	ERROR(Form("Non-numerical symbol in file %s at line %d", filename, i + 6));
	char tmp[kbuflen];
	if (fgets(tmp, kbuflen, input_file) != 0);
      }

      float time = value * ks2ps; // file holds time in seconds, while SigCh requires it in picoseconds
      float amplitude = threshold * kV2mV;  // file holds thresholds in volts, while SigCh requires it in milivolts

      reco_signal.setShapePoint(time, amplitude);
    }
  }

  // Close File
  
  fclose(input_file);

  return reco_signal;
}
*/



JPetScopeTask::JPetScopeTask(const char * name, const char * description):
  JPetTask(name, description),
  fWriter(0),
  fParamManager(0)
{
}

void JPetScopeTask::init(const JPetTaskInterface::Options& opts)
{
}

void JPetScopeTask::exec() 
{
  std::string osc_file = *(fConfig->pIter);
  std::string filename;
  
  int time_window_index;
  sscanf(path(osc_file).filename().string().c_str(), "%*3s %d", &time_window_index);
  
  JPetRecoSignal rsig1 = generateSignal(osc_file.c_str());
  rsig1.setPM(*(fConfig->pPM1));
  rsig1.setTimeWindowIndex(time_window_index);
  
  filename = path(*(fConfig->pIter)).filename().string();
  filename[1] = (fConfig->pPrefix2)[1];
  osc_file = path(*(fConfig->pIter)).parent_path().string();
  osc_file+= "/";
  osc_file+= filename;
  
  JPetRecoSignal rsig2 = generateSignal(osc_file.c_str());
  rsig2.setPM(*(fConfig->pPM2));
  rsig2.setTimeWindowIndex(time_window_index);
  
  filename = path(*(fConfig->pIter)).filename().string();
  filename[1] = (fConfig->pPrefix3)[1];
  osc_file = path(*(fConfig->pIter)).parent_path().string();
  osc_file+= "/";
  osc_file+= filename;
  
  JPetRecoSignal rsig3 = generateSignal(osc_file.c_str());
  rsig3.setPM(*(fConfig->pPM3));
  rsig3.setTimeWindowIndex(time_window_index);
  
  filename = path(*(fConfig->pIter)).filename().string();
  filename[1] = (fConfig->pPrefix4)[1];
  osc_file = path(*(fConfig->pIter)).parent_path().string();
  osc_file+= "/";
  osc_file+= filename;
  
  JPetRecoSignal rsig4 = generateSignal(osc_file.c_str());
  rsig4.setPM(*(fConfig->pPM4));
  rsig4.setTimeWindowIndex(time_window_index);
  
  fWriter->write(rsig1);
  fWriter->write(rsig2);
  fWriter->write(rsig3);
  fWriter->write(rsig4);
}

void JPetScopeTask::terminate() 
{
}
/*
JPetRecoSignal JPetScopeTask::generateSignal(const char* filename) {
  
  // Open File
  
  FILE* input_file = fopen(filename, "r");

  if (!input_file) {
    ERROR(Form("Error: cannot open file %s", filename));
    return JPetRecoSignal(0);
  }
  
  // Read Header

  int segment_size = 0;
  
  std::string fileNameWithExtension(filename);
  if(fileNameWithExtension.substr(fileNameWithExtension.find_last_of(".") + 1) != "tsv")
  {
    char buf[kbuflen];
    char tmp[kbuflen];

    if (fgets(buf, kbuflen, input_file) != 0)
    sscanf(buf, "%s %*s %*s", tmp);

    //fScopeType = tmp;

    if (fgets(buf, kbuflen, input_file) != 0)
    sscanf(buf, "%*s %*s %*s %d", &segment_size);

    if (fgets(buf, kbuflen, input_file) != 0);
    //sscanf(buf, "%*s %*s %*s");

    if (fgets(buf, kbuflen, input_file) != 0)
    sscanf(buf, "%*s %s %s %*s", tmp, tmp + kbuflen/2);

    //fDate = tmp;
    //fTime = tmp + kbuflen/2;

    if (fgets(buf, kbuflen, input_file) != 0);
    //sscanf(buf, "%*s %*s");
  }

  // Read Data

  JPetRecoSignal reco_signal(segment_size);

  for (int i = 0; i < segment_size; ++i) {
  
    float value, threshold;
    int stat;
 
    if(value >= 0.f && threshold >= 0.f)
    {
      stat = fscanf(input_file, "%f %f\n", &value, &threshold);

      if (stat != 2) {
	ERROR(Form("Non-numerical symbol in file %s at line %d", filename, i + 6));
	char tmp[kbuflen];
	if (fgets(tmp, kbuflen, input_file) != 0);
      }

      float time = value * ks2ps; // file holds time in seconds, while SigCh requires it in picoseconds
      float amplitude = threshold * kV2mV;  // file holds thresholds in volts, while SigCh requires it in milivolts

      reco_signal.setShapePoint(time, amplitude);
    }
  }

  // Close File
  
  fclose(input_file);

  return reco_signal;
}
*/
