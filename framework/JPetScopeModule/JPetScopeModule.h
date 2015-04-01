/**
 * @file JPetScopeModule.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 * @brief Module for oscilloscope data
 * Reads oscilloscope ASCII data and procudes JPetLOR structures
 */

#ifndef _SCOPE_READER_MODULE_H_
#define _SCOPE_READER_MODULE_H_

#include <cstddef>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>

#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include "../JPetScopeReader/JPetScopeReader.h"
#include "../JPetWriter/JPetWriter.h"

#define MODULE_VERSION 0.2

class JPetTreeHeader;
class JPetParamBank;

/** @brief Analysis Module for oscilloscope ASCII files.
 *
 * This module reads oscilloscope ACSII data based on config file passed through command line.
 * Example of usign this module is located in workdir/ScopeReaderExample/ .
 */
class JPetScopeModule: public JPetAnalysisModule {

  public:
  
  /** @brief Default Constructor */
  JPetScopeModule();

  /** @brief Constructor, set name and title of module through TNamed(name, title).
   *
   * @param name name of module.
   * @param title tilte of module.
   */
  JPetScopeModule(const char* name, const char* title);

  /** @brief Destructor */
  virtual ~JPetScopeModule();

  /** @brief Create list of oscilloscope ASCII files to process.
   *
   * @param inputFilename address of config file
   */
  virtual void createInputObjects(const char* inputFilename = 0);

  /** @brief Create output root file.
   * 
   * @param outputFilename address of root file.
   */
  virtual void createOutputObjects(const char* outputFilename = 0);

  /** @brief Process next group of files from fFiles.
   *
   * This method produces JPetLOR from four oscilloscope ASCII files and writes it through JPetWriter to root file.
   * @see fFiles()
   */
  virtual void exec();

  /** @brief Return number of events to be processed.
   *
   * @return number of events.
   */
  virtual long long getEventNb() {return fSize;}

  /** @brief End analysis. */
  virtual void terminate();

  /** @brief Additional method to set names of input and output files.
   *
   * @param name name of file
   */
  void setFileName(const char* name);

  /** @brief ROOT macro */
  //ClassDef(JPetScopeModule, MODULE_VERSION );

  private:
  
  long long fSize; /**< @brief Number of events to process. */
  
  int fCurrentPosition; /**< @brief Position of collimator. */

  /** @brief Collection of system parameters read from config file. */
  typedef struct configStruct {
    std::string pname; /**< @brief config name */

    JPetPM *ppm1, *ppm2, *ppm3, *ppm4; /**< @ref JPetPM. */
    JPetScin *pscin1, *pscin2; /**< @ref JPetScin. */

    JPetParamBank* pparambank; /**< @ref JPetParamBank. */

    std::string ppref1, ppref2, ppref3, ppref4; /**< @brief files prefixes. */
    std::multimap <int, std::string> pfiles; /**< @brief keys - collimator positions, values - files locations*/
    #ifndef __CINT__
    std::multimap <int, std::string> :: iterator pit; /**< @brief Iterator for pfiles. */
    #endif
  } configStruct;
  std::vector <configStruct*> fConfigs; /**< @brief Analysis system configuration. */
  #ifndef __CINT__
  std::vector <configStruct*> :: iterator fIt; /**< @brief Iterator for fConfigs. */
  #endif

  std::ifstream fConfigFile; /**< @brief Input stream from config file. */
  
  /** @brief Locations of oscilloscope ASCII data files.
   *
   * To get full name of osc file, data from fConfig is required.
   * @see fConfig()
   */

  JPetWriter* fWriter; /**< @ref JPetWriter. */
  JPetScopeReader fReader; /**< @ref JPetScopeReader. */
  JPetTreeHeader* fHeader; /**< @ref JPetTreeHeader. */
  
  TString fInFilename; /**< @brief Location of config file. */
  TString fOutFilename; /**< @brief Location of output root file. */

};

#endif
