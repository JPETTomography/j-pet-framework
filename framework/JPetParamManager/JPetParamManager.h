// JPetParamManager.h - JPetParamManager
#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <string>
#include <iostream>
//#include <TFile.h>
//#include <TList.h>

#include "../JPetScin/JPetScin.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetKB/JPetKB.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetTOMB/JPetTOMB.h"


class JPetParamManager
{
public:
  enum ContainerType {kScintillator, kPM, kKB, kTRB, kTOMB};
  
protected:
  std::string fScintilatorsObjectName;
  std::string fPMsObjectName;
  std::string fKBsObjectName;
  std::string fTRBsObjectName;
  std::string fTOMBsObjectName;
  
  std::vector<JPetScin> fScintillators;
  std::vector<JPetPM>   fPMs;
  std::vector<JPetKB>   fKBs;
  std::vector<JPetTRB>  fTRBs;
  std::vector<JPetTOMB> fTOMBs;	// to bedzie zawsze wektor jednoelementowy
  
public:
  JPetParamManager(void);
  JPetParamManager(const std::string &p_scintilatorsObjectName,
		   const std::string &p_PMsObjectName,
		   const std::string &p_KBsObjectName,
		   const std::string &p_TRBsObjectName,
		   const std::string &p_TOMBsObjectName);
  ~JPetParamManager(void);
  
  void readFile(const char* file_name);
  
  void fillScintillators(const int p_run_id);
  void fillPMs(const int p_run_id);
  void fillKBs(const int p_run_id);
  void fillTRBs(const int p_run_id);
  void fillTOMBs(const int p_run_id);
  
  void fillContainers(const int p_run_id);
  void fillContainers(const JPetParamManager::ContainerType &p_containerType, const char *p_fileName);
  
  void generateRootFile(const JPetParamManager::ContainerType &p_containerType, const char *p_fileName);
  
  template <typename T>
  std::vector<T>& getContainer(const JPetParamManager::ContainerType &p_containerType);
  template <typename T>
  bool getData(const JPetParamManager::ContainerType &p_containerType, unsigned int p_index, T &p_data);
  
  int getDataSize(const JPetParamManager::ContainerType &p_containerType) const;
  
protected:  
  void fillScintillators(const char *p_fileName);
  void fillPMs(const char *p_fileName);
  void fillKBs(const char *p_fileName);
  void fillTRBs(const char *p_fileName);
  void fillTOMBs(const char *p_fileName);
  
  void generateRootFileForScintillators(const char *p_fileName);
  void generateRootFileForPMs(const char *p_fileName);
  void generateRootFileForKBs(const char *p_fileName);
  void generateRootFileForTRBs(const char *p_fileName);
  void generateRootFileForTOMBs(const char *p_fileName);
};

#endif	// _J_PET_PARAM_MANAGER_
