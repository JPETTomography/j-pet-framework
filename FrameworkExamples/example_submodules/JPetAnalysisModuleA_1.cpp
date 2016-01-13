//
//  JPetAnalysisModuleA_1.cpp
//  
//
//  Created by Karol Stola on 22.04.2014.
//
//

#include "JPetAnalysisModuleA_1.h"

JPetAnalysisModuleA_1::JPetAnalysisModuleA_1(TTree* super_tree)
:JPetAnalysisModule("JPetAnalysisModuleA_1", "something", super_tree)
{
	
}

void JPetAnalysisModuleA_1::exec(){
	std::cout << "\n\tHere I am, the first submodule." << std::endl;
	std::cout << "\tNow I will write something to the fSuperSharedTree, so the second submodule could read it.\n" << std::endl;
}