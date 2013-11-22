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
    vector<int> tmp;
    tmp.push_back(-1);
    tmp.push_back(-1);
    
    fOptDescriptions.add_options()
    ("help,h", "produce help message")
    ("file,f", po::value<string>()->required(), "File to open")
    ("range,r", po::value< vector<int> >()->multitoken()->default_value(tmp,""), "Range of events to process.")
    ("param,p", po::value<string>(), "File with TRB numbers.")
    ;        
}

void JPetCmdParser::parse(int argc, char** argv){
    try{	
        
        po::store(po::parse_command_line(argc, argv, fOptDescriptions), fVariablesMap);
        /* print out help */
        if (fVariablesMap.count("help")) {
            cout << fOptDescriptions << "\n";
            exit(0);
        }
        
        po::notify(fVariablesMap);    
        
        /* parse range of events */
        if (fVariablesMap.count("range")) {
            if (fVariablesMap["range"].as< vector<int> >().size() != 2) {
                cerr << "Wrong number of bounds in range: " << fVariablesMap["range"].as< vector<int> >().size() << endl;
                exit(-1);
            }
            if (
                fVariablesMap["range"].as< vector<int> >()[0] 
                > fVariablesMap["range"].as< vector<int> >()[1]) 
            {
                cerr << "Wrong range of events." << endl;
                exit(-1);
            }
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