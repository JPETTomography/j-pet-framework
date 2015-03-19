/**
 * @file JPetScopeReader.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 * @brief Class for reading ASCII Oscilloscope data into JPetScopeReader structure.
 */

#ifndef _JPETSCOPEREADER_H_
#define _JPETSCOPEREADER_H_

#include <cstdio>
#include <fstream>
#include <string>

#include "../JPetRecoSignal/JPetRecoSignal.h"

/** @brief Oscilloscope ASCII data reader.
 * JPetScopeReader class produce JPetSignal from single oscilloscope ASCII file.
 */
class JPetScopeReader {
  
  public:

  /** @brief Default Constructor */
  JPetScopeReader();

//  JPetScopeReader(const char* filename);

  /** @brief Destructor */
  virtual ~JPetScopeReader();

  /** @brief Produce JPetSignal from given file.
   *
   * If setPrintFile(true) method was called data is also printed on screen.
   *
   * @param filename address of an oscilloscope ASCII file.
   * @return reference to created JPetRecoSignal
   * @see setPrintFile()
   */
  JPetRecoSignal& generateSignal (const char* filename);

  /** @brief Return id of photomultiplier set by JPetScopeModule
   * @return fPMID
   */
  inline int getPMID() const {return fPMID;}
    
  //inline int getSegments() const {return fSegments;}

  /** @brief Return number of data lines (JPetSigCh contained in output JPetSignal).
   * @return fSegmentSize
   */
  inline int getSegmentSize() const {return fSegmentSize;}
 
  /** @brief Debug function
   * @param print if true generateSignal will print every data line read.
   * @see generateSignal()
   */
  inline void setPrintFile (bool print = true) {fPrintFile = print;}

  /** @brief Set ID of photomultiplier used to gather signal.
   * @param PMID id of photomultiplier
   */
  inline void setPMID(int PMID) {fPMID = PMID;}

  private:

  /** @brief Open file method.
   * @param address of file to open.
   */
  void openFile(const char* filename);
  
  /** @brief Check if file is opend
   * @return ture if file is opend, flase if not.
   */
  inline bool isFileOpen() const {return fInputFile;}

  /** @brief Close file method. */
  void closeFile();

  /** @brief Reads header of oscilloscope ASCII file */
  void readHeader();

  /** @brief Reads data from oscilloscope ASCII file and produces JPetSignal
   *
   * If setPrintFile(true) method was called data is also printed on screen.
   *
   * @return reference to JPetRecoSignal.
   * @see setPrintFile()
   */
  JPetRecoSignal& readData();

  FILE* fInputFile; /**< @brief Pointer to oscilloscope ASCII file. */

  std::string fScopeType; /**< @brief Oscilloscope type read form file header. */
  std::string fDate; /**< @brief Date, when signal was gathered. */
  std::string fTime; /**< @brief Time, when signal was gathered. */
  std::string fFilename; /** @brief Address of oscilloscope ASCII file. */

  /** @brief Debug flag.
   *
   * If true data read will be printed on screen.
   * @see setPrintFile()
   */
  bool fPrintFile;

  int fPMID; /**< @brief ID of photomultiplier used to gather signal. */
  //int fSegments;
  int fSegmentSize; /**< @brief Number of data lines in file. */

  JPetRecoSignal fRecoSignal; /**< @brief Last created JPetRecoSignal. */
  
};

#endif
