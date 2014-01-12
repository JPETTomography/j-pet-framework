#include "JPetHLDReader.h"
#include <iostream>

bool JPetHLDReader::OpenFile (const char* filename){
	JPetReader::OpenFile(filename);
	ReadData("T");
	
}