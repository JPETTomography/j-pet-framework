/*
 *  JPetCmdParser.cpp
 *  
 *
 *  Created by Karol Stola on 13-11-22.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "JPetCmdParser.h"

//#ifndef __CINT__ // guard against being included into dictionary

JPetCmdParser::JPetCmdParser()
    : fOptDescriptions("Allowed options")
{
    fOptDescriptions.add_options()
    ("help,h", "produce help message")
    ("file,f", po::value<string>(), "File to open")
    ("range,r", po::value< vector<int> >(), "Range of events to process.")
    ("param,p", po::value<string>(), "File with TRB numbers.")
    ;
        
}

void JPetCmdParser::parse(int argc, char** argv){
    try{	
        
        po::store(po::parse_command_line(argc, argv, fOptDescriptions), fVariablesMap);
        po::notify(fVariablesMap);    
		
        if (fVariablesMap.count("help")) {
            cout << fOptDescriptions << "\n";
            return;
        }
        
        if (fVariablesMap.count("file")) {
            cout << "File to open:  " 
            << fVariablesMap["file"].as<string>() << ".\n";
        }
        else {
            cout << "File to open was not specified.\n";
        }
    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }
}

//#endif /* __CINT__ */