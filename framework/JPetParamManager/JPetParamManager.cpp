#include "JPetParamManager.h"
//#include "../DBHandler/HeaderFiles/ParamServer.h"
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "../JPetKB/JPetKB.h"


using namespace std;

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
