/**
 *  @file JPetTreeHeader.h
 *  @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 */
#ifndef _JPET_TREE_HEADER_H_
#define _JPET_TREE_HEADER_H_

#include <TObject.h>
#include <TString.h>
#include <iostream>
#include <ostream>
#include <vector>

/**
 * @brief A class representing a header with info on JPet ROOT Trees.
 *
 * Encapsulates information from the top-level of JPet data files as defined in Report 19, tables 37+. A TreeHeader object is intended to be stored in evert JPet ROOT file along with a respective TTree which it describes.
 */
class JPetTreeHeader: public TObject{
 public:
  JPetTreeHeader() {};
  JPetTreeHeader( int run, TString producer = "", int version = -1 );
  void Print(Option_t* opt = "") const {
    std::cout << this->Stringify();
  }
  /// produce a TString edscribing all the information dontained in this object
  TString Stringify() const;

  // Get name of the mudule which produced this tree
  inline const TString & GetProducerName() const { return fProducerName; }
  // Get version of the mudule which produced this tree
  inline int GetProducerVersion()  const { return fProducerVersion; }
  // Get number if the run from whose data this tree was produced
  inline int GetRunNumber()  const { return fRunNo; }
  
  // Set name of the mudule which produced this tree
  inline void SetProducerName(TString name) { fProducerName = name; }
  // Set version of the mudule which produced this tree
  inline void SetProducerVersion(int version) { fProducerVersion = version; }
  
  /**
   * @brief Add information on a raw HLD file used in this run
   *
   * @param name a string with the filename of the raw HLD file
   * @param id ID of the run
   * @param nEvts number of time windows contained in the raw HLD file
   * @param width width of the DAQ time window in picoseconds
   * @param firstEvt number if the first TSlot belonging to this file
   * @param startT absolute starting time of the measurement constained in this file
   *
   * It is possible to produce one ROOT Tree with porocessed data from multiple HLD files. In such a case, this method should be called for each file used. The events from multiple files would be put subsequently into one tree, and then the startT and firstEvt values should be provided. 
   *
   */
  int addHLDinfo(TString name, int id, int nEvts, float width, 
		 int firstEvt=0., double startT=0.);
  /// Get the number of HLD files used to produce the Tree described byb this header
  int getNoHLDfiles() { return fHLDnames.size(); }
  
  /// Get file name of HLD file number no
  TString getHLDname(int no) const;
  /// Get run ID for HLD file number no
  int getHLDid(int no) const;
  /// Get number of events in HLD file number no
  int getHLDnEvts(int no) const;
  /// Get the width of time window for HLD file number no, in picoseconds
  float getHLDwindowWidth(int no) const;
  int getHLDfirstEvt(int no) const;
  double getHLDstartTime(int no) const;

  ClassDef(JPetTreeHeader, 1);

protected:
  TString fProducerName;
  int fProducerVersion;
  int fRunNo;

  std::vector<TString> fHLDnames;
  std::vector<int> fHLDids;
  std::vector<float> fHLDwinWidths;
  std::vector<int> fHLDnEvts;
  std::vector<int> fHLDfirstEvt;
  std::vector<double> fHLDstartTimes;

};


/* ostream& operator<<(ostream& os, const JPetTreeHeader& header){ */
/*   os << header.Stringify(); */
/*   return os; */
/* } */

#endif
