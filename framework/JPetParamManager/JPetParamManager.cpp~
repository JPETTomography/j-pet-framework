#include "JPetParamManager.h"
//#include "../DBHandler/HeaderFiles/ParamServer.h"
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "../JPetKB/JPetKB.h"
#include "../CommonTools/CommonTools.h"


using namespace std;

JPetParamManager::JPetParamManager(const std::string &p_KBsDataObjectName) : m_KBsDataObjectName(p_KBsDataObjectName)
{
}

void JPetParamManager::readFile(const char * file_name){
	assert(file_name != NULL);
	
	string line;
	
	ifstream file(file_name);
	if( ! file.is_open() ){
		ERROR("No such file!");
		return;
	}
	
	while ( !file.eof() ){
		int trb = 0, scin = 0;
		
		getline(file, line);
		istringstream iss(line);
		
		iss >> trb;
		iss >> scin;
		fTRBNumbers.push_back(trb);
		fScinNumbers.push_back(scin);
	}
}

void JPetParamManager::fillKBsData(int p_run_id)
{
  DB::SERVICES::DBHandler &l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();
  
  std::string l_run_id = boost::lexical_cast<std::string>(p_run_id);
  std::string l_sqlQuerry = "SELECT * FROM getKonradBoardsData(" + l_run_id + ");";
  pqxx::result l_runDbResults = l_dbHandlerInstance.querry(l_sqlQuerry);

  size_t l_sizeResultQuerry = l_runDbResults.size();

  if(l_sizeResultQuerry)
  {
    for(pqxx::result::const_iterator row = l_runDbResults.begin(); row != l_runDbResults.end(); ++row)
    {
      int l_konradboard_id = row["konradboard_id"].as<int>();
      bool l_konradboard_isactive = row["konradboard_isactive"].as<bool>();
      std::string l_konradboard_status = row["konradboard_status"].as<std::string>();
      std::string l_konradboard_description = row["konradboard_description"].as<std::string>();
      int l_konradboard_version = row["konradboard_version"].as<int>();
      int l_konradboard_creator_id = row["konradboard_creator_id"].as<int>();

      JPetKB l_KB(
		  l_konradboard_id, 
		  l_konradboard_isactive, 
		  l_konradboard_status, 
		  l_konradboard_description, 
		  l_konradboard_version, 
		  l_konradboard_creator_id
		 );
      
      m_KBsData.push_back(l_KB);
    }
  }
}

void JPetParamManager::fillKBsData(const char *p_fileName)
{
  std::string l_fileToSave = p_fileName;
  if(CommonTools::findSubstring(l_fileToSave, std::string(".root")) == string::npos)
  {
    l_fileToSave.append(".root");
  }
  
  TFile* file1 = new TFile (l_fileToSave.c_str(), "READ", "", 0);
  TList* dblist = (TList*)file1->Get(m_KBsDataObjectName.c_str());
  
  TObject *obj;
  
  TIter next(dblist);
  while((obj = next()))
  {
    JPetKB *l_kb = static_cast<JPetKB*>(obj);
    std::cout << "l_kb->isActive() = " << l_kb->isActive() << std::endl;
    m_KBsData.push_back(*l_kb);
  }

  delete file1;
}

void JPetParamManager::generateRootFileWithKBsData(const char *p_fileName)
{
  if(!m_KBsData.empty())
  {
    std::string l_fileToSave = p_fileName;
    if(CommonTools::findSubstring(l_fileToSave, std::string(".root")) == string::npos)
    {
      l_fileToSave.append(".root");
    }
    
    TFile* file1 = new TFile (l_fileToSave.c_str(), "RECREATE", "", 0);

    TList* dblist = new TList();

    for(std::vector<JPetKB>::iterator it = m_KBsData.begin(); it != m_KBsData.end(); ++it)
    {
      dblist->Add(&(*it));
    }

    file1->WriteObject(dblist, m_KBsDataObjectName.c_str());
    file1->Close();

    delete file1;
    delete dblist;
  }
}
