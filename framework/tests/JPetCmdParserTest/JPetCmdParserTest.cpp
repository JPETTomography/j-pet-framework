/**
  *  @copyright Copyright (c) 2014, J-PET collaboration
  *  @file JPetCmdParserTest.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCmdParserTest
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#define private public
#define protected public
#include "../../JPetCmdParser/JPetCmdParser.h"

//public method
//std::vector<JPetOptions> parseAndGenerateOptions(int argc, const char** argv);

using namespace std;

char* convertStringToCharP(const std::string& s)
{
  char* pc = new char[s.size() + 1];
  std::strcpy(pc, s.c_str());
  return pc;
}

std::vector<char*> createArgs(const std::string& commandLine) 
{
  std::istringstream iss(commandLine);
  std::vector<std::string> args {std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}
                                };
  std::vector<char*> args_char;
  std::transform(args.begin(), args.end(), std::back_inserter(args_char), convertStringToCharP);
  return args_char;
}

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( parsing_1 )
{
  auto commandLine = "main.x -t hld -f testfile.hld -i 10";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE(std::string(option.getInputFile()) == "testfile.hld");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), 10);
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kHld);
}

BOOST_AUTO_TEST_CASE( parsing_2 )
{
  auto commandLine = "main.x -t scope -f testfile.json ";
  auto args_char = createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();

  JPetCmdParser parser;
  auto options = parser.parseAndGenerateOptions(argc, const_cast<const char**>(argv));
  BOOST_REQUIRE_EQUAL(options.size(), 1);
  auto option = options.at(0);
  BOOST_REQUIRE(std::string(option.getInputFile()) == "testfile.json");
  BOOST_REQUIRE_EQUAL(option.getFirstEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getLastEvent(), -1);
  BOOST_REQUIRE_EQUAL(option.getRunNumber(), -1);
  BOOST_REQUIRE(!option.isProgressBar());
  BOOST_REQUIRE_EQUAL(option.getInputFileType(), JPetOptions::kScope);
}
/*
  ("help,h", "produce help message")
  ("type,t", po::value<std::string>()->required(), "type of file: hld, root or scope")
  ("file,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open")
  ("range,r", po::value< std::vector<int> >()->multitoken()->default_value(tmp, ""), "Range of events to process.")
  ("param,p", po::value<std::string>(), "File with TRB numbers.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", "Progress bar.");
*/
BOOST_AUTO_TEST_CASE(getOptionsDescriptionTest)
{
    JPetCmdParser cmdParser;
    auto optionDescription = cmdParser.getOptionsDescription();
    //optionDescription.add
    //optionDescription.find()
    cout << "andrzej" << endl;
    auto helpOptionDescription = optionDescription.find("help", true);
    //cout << helpOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(helpOptionDescription.description()) == "produce help message");
    //cout << helpOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(helpOptionDescription.format_name()) == "-h [ --help ]");

    auto typeOptionDescription = optionDescription.find("type", true);
    //cout << typeOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(typeOptionDescription.description()) == "type of file: hld, root or scope");
    //cout << typeOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(typeOptionDescription.format_name()) == "-t [ --type ]");

    auto fileOptionDescription = optionDescription.find("file", true);
    //cout << fileOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(fileOptionDescription.description()) == "File(s) to open");
    //cout << fileOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(fileOptionDescription.format_name()) == "-f [ --file ]");

    auto rangeOptionDescription = optionDescription.find("range", true);
    //cout << rangeOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(rangeOptionDescription.description()) == "Range of events to process.");
    //cout << rangeOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(rangeOptionDescription.format_name()) == "-r [ --range ]");

    auto paramOptionDescription = optionDescription.find("param", true);
    //cout << paramOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(paramOptionDescription.description()) == "File with TRB numbers.");
    //cout << paramOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(paramOptionDescription.format_name()) == "-p [ --param ]");

    auto runIdOptionDescription = optionDescription.find("runId", true);
    //cout << runIdOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(runIdOptionDescription.description()) == "Run id.");
    //cout << runIdOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(runIdOptionDescription.format_name()) == "-i [ --runId ]");

    auto progressBarOptionDescription = optionDescription.find("progressBar", true);
    //cout << progressBarOptionDescription.description() << endl;
    BOOST_REQUIRE(std::string(progressBarOptionDescription.description()) == "Progress bar.");
    //cout << progressBarOptionDescription.format_name() << endl;
    BOOST_REQUIRE(std::string(progressBarOptionDescription.format_name()) == "-b [ --progressBar ]");
}

BOOST_AUTO_TEST_CASE(fileTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -f data.hld";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("file,f", po::value<std::vector<std::string>>(), "File(s) to open")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    auto fileNames = cmdParser.getFileNames(variablesMap);
    BOOST_REQUIRE(fileNames.size() == 1);
    BOOST_REQUIRE(fileNames.front() == "data.hld");

    auto file = variablesMap["file"].as<std::vector<std::string>>();
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("file") == 1);
    BOOST_REQUIRE(file.front() == "data.hld");
}

BOOST_AUTO_TEST_CASE(fileTypeTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -t hld";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("type,t", po::value<std::string>(), "type of file: hld, root or scope")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    auto fileType = variablesMap["type"].as<std::string>();

    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("type") > 0);
    BOOST_REQUIRE(fileType == "hld");
    BOOST_REQUIRE(cmdParser.isCorrectFileType(fileType));
    BOOST_REQUIRE(cmdParser.getFileType(variablesMap) == "hld");
    BOOST_REQUIRE(cmdParser.IsFileTypeSet(variablesMap));
}

BOOST_AUTO_TEST_CASE(rangeTest)
{
    JPetCmdParser cmdParser;

    auto commandLine = "main.x -r 4";
    auto args_char = createArgs(commandLine);
    auto argc = args_char.size();
    auto argv = args_char.data();

    po::options_description description("Allowed options");
    description.add_options()
            ("range,r", po::value<std::vector<int>>(), "Range of events to process.")
    ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);
    po::notify(variablesMap);

    BOOST_REQUIRE(cmdParser.getLowerEventBound(variablesMap) == 4);

    auto range = variablesMap["range"].as<std::vector<int>>();
    BOOST_REQUIRE(variablesMap.size() == 1);
    BOOST_REQUIRE(variablesMap.count("range") == 1);
    BOOST_REQUIRE(range.front() == 4);
}
/* To remove */
BOOST_AUTO_TEST_CASE(dummyTest)
{
    JPetCmdParser cmdParser;
    po::variables_map variablesMap;
    //variablesMap.insert()
    //BOOST_REQUIRE(!cmdParser.IsFileTypeSet(variablesMap));
    //cmdParser.generateOptions(variablesMap);
    //BOOST_REQUIRE(cmdParser.areCorrectOptions(variablesMap));

    // Declare the supported options.

    auto commandLine = "main.x -h help -c 10";
    auto args_char = createArgs(commandLine);
    auto ac = args_char.size();
    auto av = args_char.data();

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("compression,c", po::value<int>(), "set compression level")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
    }

    if (vm.count("compression")) {
        cout << "Compression level was set to "
     << vm["compression"].as<int>() << ".\n";
    } else {
        cout << "Compression level was not set.\n";
    }
}

BOOST_AUTO_TEST_SUITE_END()
