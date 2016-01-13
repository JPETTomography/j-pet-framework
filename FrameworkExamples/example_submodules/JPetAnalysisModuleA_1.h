//
//  JPetAnalysisModuleA_1.h
//  
//
//  Created by Karol Stola on 22.04.2014.
//
//

#ifndef ____JPetAnalysisModuleA_1__
#define ____JPetAnalysisModuleA_1__

#include <iostream>
#include <JPetAnalysisModule/JPetAnalysisModule.h>


class JPetAnalysisModuleA_1 : public JPetAnalysisModule {

public:
	JPetAnalysisModuleA_1(TTree* super_tree);
	virtual void createInputObjects(const char* inputFilename=0){}
	virtual void createOutputObjects(const char* outputFilename=0){}
	virtual void exec();
	virtual long long getEventNb(){}
	virtual void terminate(){}

};

#endif /* defined(____JPetAnalysisModuleA_1__) */
