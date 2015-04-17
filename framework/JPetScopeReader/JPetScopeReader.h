/**
 * @file JPetScopeReader.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2015, Damian Trybek
 * @brief Module for oscilloscope data
 * Reads oscilloscope ASCII data and procudes JPetRecoSignal structures.
 */

#ifndef _SCOPE_READER_MODULE_H_
#define _SCOPE_READER_MODULE_H_

#define MODULE_VERSION 0.4

#include "../JPetAnalysisModule/JPetAnalysisModule.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include <boost/property_tree/ptree.hpp>

class JPetParamBank;
class JPetPM;
class JPetRecoSignal;
class JPetScin;
class JPetTreeHeader;
class JPetWriter;

/** @brief Analysis Module for oscilloscope ASCII files.
 *
 * This module reads oscilloscope ACSII data based on config file passed through command line.
 * Example of usign this module is located in workdir/ScopeReaderExample/ .
 */
class JPetScopeReader: public JPetAnalysisModule {
  
  private:
  
  /** @brief Collection of system parameters read from config file.
   *
   * One object per signle configuration + collimator position is created.
   */
  typedef struct ScopeConfig {
    
    std::string pName; /**< @brief Config name. */
    int pCollPosition; /**< @brief Collimator position. */

    JPetParamBank const* pParamBank; /**< @brief Pointer to JPetParamBank for current configuration.
                                      *
				      * @ref JPetParamBank
				      */
    
    JPetPM *pPM1, *pPM2, *pPM3, *pPM4; /**< @ref JPetPM */
    JPetScin *pScin1, *pScin2; /**< @ref JPeScin */

    std::string pPrefix1, pPrefix2, pPrefix3, pPrefix4; /**< @brief Oscilloscope ACII files prefixes. */

    std::set <std::string> pFiles; /**< @brief Set of files to process. */
    std::set <std::string> :: iterator pIter; /**< @ref pIter */

  } ScopeConfig;

  public:

  /** @brief Default Constructor.
   */
  JPetScopeReader();

  /** @brief Constructor
   *
   * @param name Module name.
   * @param title Short description.
   */
  JPetScopeReader(const char* name, const char* title);

  /* @brief Default Destructor.
   */
  virtual ~JPetScopeReader();

  /** @brief Prepare list of input files.
   *
   * Parse config file, prepare list of oscilloscope ASCII files to be processed and prepares parameters bank.
   *
   * @param inputFilename Config file name.
   */
  virtual void createInputObjects(const char* inputFilename = 0);

  /** @brief Required by JPetManager.
   *
   * Currently does nothing
   */
  virtual void createOutputObjects(const char* outputFilename = 0);

  /** @brief Execute analysis for single event.
   *
   * Function containing per event analysis.
   */
  virtual void exec();
  
  /** @brief Return number of events to be processed.
   *
   * @return fEventNb
   */
  virtual long long getEventNb() {return fEventNb;}
  
  /** @brief End analysis.
   */
  virtual void terminate();

  /** @biref Set input file name.
   *
   * @param name input file name.
   */
  void setFileName(const char* name);
  
  /** @brief Create writer for new configuration.
   *
   * When processing events for new configuration new output file is created.
   */
  void createNewWriter(const char* outputFilename = 0);

  /** @brief Create bank with system describing objects.
   *
   * Param bank is created basing on configuration file.
   * 
   * @param conf_data branch of property tree for single configuration.
   * @return JPetParamBank with data describing current configuration.
   *
   * @todo Add possibility to read parameters for SQL database.
   */
  JPetParamBank const& createParamBank (boost::property_tree::ptree const& conf_data);

  /** @brief Produce JPetRecoSignal from single oscilloscope ASCII file.
   *
   * Functionality of old JPetScopeReader.
   *
   * @param filename oscilloscpe ASCII filename.
   * @return generated JPetRecoSignal
   */
  static JPetRecoSignal generateSignal (const char* filename);

  private:

  long long fEventNb; /**< @brief Number of events to process. */ 
  
  JPetTreeHeader* fHeader; /**< @ref JPetTreeHeader. */ 
  JPetWriter* fWriter; /**< @ref JPetWriter. */

  TString fInFilename; /**< @brief Location of config file. */
  TString fOutFilename; /**< @brief Location of output root file. */

  std::vector <ScopeConfig> fConfigs; /**< @brief Vector of all configurations.
                                       * 
				       * @ref ScopeConfig
				       */

  std::vector <ScopeConfig> :: iterator fIter; /**< @ref fConfigs */

};

#endif
