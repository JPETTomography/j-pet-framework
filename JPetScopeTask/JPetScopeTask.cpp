#include "../JPetScopeTask/JPetScopeTask.h"
#include "../JPetParamManager/JPetParamManager.h"

#include <iostream>
#include <string>
#include "JPetScopeTaskUtils.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;


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
