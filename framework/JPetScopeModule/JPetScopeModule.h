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

#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include "../JPetScopeReader/JPetScopeReader.h"
#include "../JPetWriter/JPetWriter.h"

#define MODULE_VERSION 0.1

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
  void saveNewTreeFile();
  void createNewWriter(int position);

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
  virtual long long getEventNb() {return fFiles.size();}

  /** @brief End analysis. */
  virtual void terminate();

  /** @brief Additional method to set names of input and output files.
   *
   * @param name name of file
   */
  void setFileName(const char* name);

  /** @brief Debug function.
   *
   * This function prints list of all collimator positions, that will be processed.
   */
  virtual void printCollPositions ();

  /** @brief Debug function.
   *
   * This function prints list of all files, that will be processed.
   */
  virtual void printFiles();

  /** @brief ROOT macro */
  ClassDef(JPetScopeModule, MODULE_VERSION );

  private:
  
  /** @brief Config file reader function.
   *
   * Read single config line using vsscanf function.
   * @param fmt format passed to vsscanf.
   */
  int readFromConfig (const char* fmt, ...);

  int fCurrentPosition; /**< @brief Position of collimator. */

  /** Collection of system parameters read from config file. */
  typedef struct configStruct {
    int pm1, pm2, pm3, pm4; /**< @brief ID's of photomultipliers. */
    JPetPM *ppm1, *ppm2, *ppm3, *ppm4; /**< @ref JPetPM. */
    JPetScin *pscin1, *pscin2; /**< @ref JPetScin. */
    std::string file1, file2, file3, file4; /**< @brief Names (not locations) of data oscilloscope ASCII data files. */
    int scin1, scin2; /**< @brief ID's of scintillators. */
    int collimator; /**< @brief Collimator position. */
  } configStruct;
  configStruct fConfig; /**< @brief Analysis system configuration. */

  std::ifstream fConfigFile; /**< @brief Input stream from config file. */
  
  /** @brief Locations of oscilloscope ASCII data files.
   *
   * To get full name of osc file, data from fConfig is required.
   * @see fConfig()
   */
  std::multimap <int, std::string> fFiles;
  std::set <int> fCollPositions; /**< @brief Set of collimator positions. */

  JPetWriter* fWriter; /**< @ref JPetWriter. */
  JPetScopeReader fReader; /**< @ref JPetScopeReader. */
  JPetTreeHeader* fHeader; /**< @ref JPetTreeHeader. */

  JPetParamBank* fParamBank; /**< @ref JPetParamBank. */
  
  TString fInFilename; /**< @brief Location of config file. */
  TString fOutFilename; /**< @brief Location of output root file. */

};

#endif
