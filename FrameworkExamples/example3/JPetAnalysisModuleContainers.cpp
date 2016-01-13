#include "./JPetAnalysisModuleContainers.h"

#include <JPetSigCh/JPetSigCh.h>
#include <JPetSignal/JPetSignal.h>

#include <TSystem.h>



ClassImp(JPetAnalysisModuleContainers);


JPetAnalysisModuleContainers::JPetAnalysisModuleContainers() : JPetAnalysisModule(), m_manager(JPetManager::GetManager()), fEventNb(0)
{
}

JPetAnalysisModuleContainers::JPetAnalysisModuleContainers(const char* name, const char* title) : JPetAnalysisModule(name, title), m_manager(JPetManager::GetManager()), fEventNb(0)
{
}

JPetAnalysisModuleContainers::~JPetAnalysisModuleContainers()
{
}

void JPetAnalysisModuleContainers::createInputObjects(const char* inputFilename)
{ 
  std::cout << "createInputObjects\n" << std::endl;

  // TESTs for JPetParamManager with std::vector<> implementation
  /*
  JPetWriter l_writer("TEST.root");//wskaznik writera i readera jest paramManager
  
  JPetScin l_scintillator(1, 2.f, 3.f, 4.f, 5.f);
  JPetPM l_PM;
  JPetFEB l_KB(1, false, "Status", "Description", 1, 1);
  JPetTRB l_TRB;
  
  //SCIN
  m_manager.getParamManagerInstance().addScintillator(l_scintillator);
  std::cout << m_manager.getParamManagerInstance().getScintillator(0)->getID() << std::endl;
  m_manager.getParamManagerInstance().getScintillator(0)->setLeftTRefPM(l_PM);
  
  JPetPM *l_TRefPM = m_manager.getParamManagerInstance().getScintillator(0)->getTRefPMLeft();
  std::cout << "l_TRefPM->getID() = " << l_TRefPM->getID() << std::endl;

  //l_writer.write(m_manager.getParamManagerInstance().getScintillators());
  
  //PM
  m_manager.getParamManagerInstance().addPM(l_PM);
  std::cout << m_manager.getParamManagerInstance().getPM(0)->getID() << std::endl;
  m_manager.getParamManagerInstance().getPM(0)->setTRefKB(l_KB);

  JPetFEB *l_TRefKB = m_manager.getParamManagerInstance().getPM(0)->getTRefKB();
  std::cout << "l_TRefKB->id() = " << l_TRefKB->id() << std::endl;
  
  //l_writer.write(m_manager.getParamManagerInstance().getPMs());

  //KB
  m_manager.getParamManagerInstance().addKB(l_KB);
  std::cout << m_manager.getParamManagerInstance().getKB(0)->id() << std::endl;
  m_manager.getParamManagerInstance().getKB(0)->setTRefTRB(l_TRB);

  JPetTRB *l_TRefTRB = m_manager.getParamManagerInstance().getKB(0)->getTRefTRB();
  std::cout << "l_TRefTRB->getID() = " << l_TRefTRB->getID() << std::endl;
  
  //l_writer.write(m_manager.getParamManagerInstance().getKBs());  
  
  //TRB
  m_manager.getParamManagerInstance().addTRB(l_TRB);
  std::cout << m_manager.getParamManagerInstance().getTRB(0)->getID() << std::endl;

  
  //l_writer.write(m_manager.getParamManagerInstance().getKBs());    
  
  
  */
};

void JPetAnalysisModuleContainers::createOutputObjects(const char* outputFilename)
{
  std::cout << "createOutputObjects\n" << std::endl;
}

void JPetAnalysisModuleContainers::exec()
{
}

void JPetAnalysisModuleContainers::terminate() 
{
}
