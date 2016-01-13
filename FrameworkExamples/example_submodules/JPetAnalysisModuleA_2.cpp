//
//  JPetAnalysisModuleA_2.cpp
//  
//
//  Created by Karol Stola on 22.04.2014.
//
//

#include "JPetAnalysisModuleA_2.h"

JPetAnalysisModuleA_2::JPetAnalysisModuleA_2(TTree* super_tree)
	:JPetAnalysisModule("JPetAnalysisModuleA_2", "something", super_tree)
{
	
}


void JPetAnalysisModuleA_2::exec(){
	std::cout << "\n\tHere I am, the second submodule." << std::endl;
	std::cout << "\tNow I will read what the first submodule wrote to fSuperSharedTree," << std::endl;
	std::cout << "\tclean it and write over what I have done with it, so The main module could read it." << std::endl;
}