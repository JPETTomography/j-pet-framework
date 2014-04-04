/**
 *  @copyright Copyright (c) 2014, J-PET collaboration
 *  @file JPetCmdParser.cpp
 *  @author Karol Stola
 */

#include "JPetCmdParser.h"

using namespace std;

JPetCmdParser::JPetCmdParser()
  : fOptDescriptions("Allowed options")
{
  vector<int> tmp;
  tmp.push_back(-1);
  tmp.push_back(-1);

  fOptDescriptions.add_options()
  ("help,h", "produce help message")
  ("type,t", po::value<string>()->required(), "type of file: hld or root")
  ("file,f", po::value<string>()->required(), "File to open")
  ("range,r", po::value< vector<int> >()->multitoken()->default_value(tmp, ""), "Range of events to process.")
  ("param,p", po::value<string>(), "File with TRB numbers.")
  ;
}

void JPetCmdParser::parse(int argc, char** argv)
{
  try {

    if (argc == 1) {
      cout << "No options provided." << endl;
      cout << fOptDescriptions << "\n";
      exit(0);
    }

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
          > fVariablesMap["range"].as< vector<int> >()[1]) {
        cerr << "Wrong range of events." << endl;
        exit(-1);
      }
    }

    /* check if correct file type was provided */

    if (
        fVariablesMap["type"].as <string>().compare("hld")
        && fVariablesMap["type"].as <string>().compare("root")
    ) {
      cerr << "Wrong type of file: " << fVariablesMap["type"].as< string >() << endl;
      cerr << "Possible options: hld or root" << endl;
      exit(-1);
    }

  } catch (exception& e) {
    cerr << "error: " << e.what() << "\n";
    return;
  } catch (...) {
    cerr << "Exception of unknown type!\n";
  }
}

//#endif /* __CINT__ */
