#include "../../JPetScopeReader/JPetScopeReader.h"

#include <cstddef>
#include <cstdio>

#include "../../JPetRecoSignal/JPetRecoSignal.h"

// *********************************************************************** //
// ********            Generate Single JPetRecoSignal             ******** //
// *********************************************************************** //

const char* filename = "test_signal.txt";

struct generate_reco_signal {
  
  public:
  
  generate_reco_signal ();
  generate_reco_signal (const char*);

  ~generate_reco_signal ();

  int setup (const char*);

  public:

  int check_header (void (*unit_test_function) (int, int) = nullptr);
  int check_data (void (*unit_test_function) (float, float, float, float) = nullptr);

  private:

  int m_segment_size;
  
  JPetRecoSignal m_reco_signal;

  FILE* m_file;

};

// *********************************************************************** //

generate_reco_signal::generate_reco_signal () : m_file(nullptr) {
}

// *********************************************************************** //

generate_reco_signal::generate_reco_signal (const char*) : m_file(nullptr) {
}

// *********************************************************************** //

generate_reco_signal::~generate_reco_signal () {

  if (m_file != nullptr) fclose (m_file);
}

// *********************************************************************** //

int generate_reco_signal::setup (const char* filename) {
  
  m_reco_signal = JPetScopeReader::generateSignal (filename);
  m_file = fopen(filename, "r");

  return 0;
}

// *********************************************************************** //

int generate_reco_signal::check_header (void (*unit_test_function) (int, int)) {
  
  rewind (m_file);
  
  const int kbuflen = 256;
  char buf[kbuflen];
  if (fgets(buf, kbuflen, m_file) != 0);

  if (fgets(buf, kbuflen, m_file) != 0)
  sscanf(buf, "%*s %*s %*s %d", &m_segment_size);

  if (fgets(buf, kbuflen, m_file) != 0);
  if (fgets(buf, kbuflen, m_file) != 0);
  if (fgets(buf, kbuflen, m_file) != 0);

  if (unit_test_function != nullptr) {
    (*unit_test_function) (m_segment_size, m_reco_signal.getShape().size());
  }

  return 0;
}

// *********************************************************************** //

int generate_reco_signal::check_data (void (*unit_test_function) (float, float, float, float)) {
  
  check_header(nullptr);

  for (int i = 0; i < m_segment_size; ++i) {
    
    const double ks2ps = 1.0e+12;
    const double kV2mV = 1.0e+3;
    const int kbuflen = 256;
    
    float value, threshold;
    int stat;
 
    stat = fscanf(m_file, "%f %f\n", &value, &threshold);

    if (stat != 2) {
      ERROR(Form("Non-numerical symbol at line %d", i + 6));
      char tmp[kbuflen];
      if(fgets(tmp, kbuflen, m_file));
    }

    float time = value * ks2ps;
    float amplitude = threshold * kV2mV;

    if (unit_test_function != nullptr) {
      (*unit_test_function) (time, m_reco_signal.getShape()[i].time, amplitude, m_reco_signal.getShape()[i].amplitude);
    }
  }

  return 0;
}

// *********************************************************************** //
// ********               Signal Generation Fixture               ******** //
// *********************************************************************** //

struct signal_generate_fixture : public generate_reco_signal {
  
  public:

  signal_generate_fixture ();
  ~signal_generate_fixture ();

};

// *********************************************************************** //

signal_generate_fixture::signal_generate_fixture () : generate_reco_signal() {
  generate_reco_signal::setup(filename);
}

// *********************************************************************** //

signal_generate_fixture::~signal_generate_fixture () {
}

/*#include <boost/property_tree/ptree.h>

#include <string>

class ParseConfigFileFixture {
  
  public:

  ParseConfigFileFixture();
  ~ParseConfigFileFixture();

  int Setup (const char* configFile, boost::property_tree::ptree* pTree) {

    std::string ext = path(fInFilename).extension().string();

    // Read configuration data to property tree
  
    if (ext.compare(".ini") == 0) {
      read_ini(fInFilename.Data(), m_ptree);
    } else if (ext.compare(".info") == 0) {
      read_info(fInFilename.Data(), m_ptree);
    } else if (ext.compare(".json") == 0) {
      read_json(fInFilename.Data(), m_ptree);
    } else if (ext.compare(".xml") == 0) {
      read_xml(fInFilename.Data(), m_ptree);
    } else {
      return 1;
    }
    return 0;
  }

  private:

  boost::property_tree::ptree m_ptree;
};

class GenerateEventsFixture {

  public:

  GenerateEventsFixture();
  ~GenerateEventsFixture();
  
  int Setup (const char* configFile, boost::property_tree::ptree* pTree) {
    return 0;
  }
};

class CleanROOTStaticDataFixture {
  
  public:

  CleanROOTStaticDataFixture();
  ~CleanROOTStaticDataFixture();

  int Setup (const char* configFile, boost::property_tree::ptree* pTree) {
    return 0;
  }
};

class ScopeModuleTestFixtures : public ParseConfigFileFixture
                                public GenerateEventsFixture,
                                public CleanROOTStaticDataFixture,
				public LoadEventsFixtur{
  
  public:

  ScopeModuleTestFixtures (const char* configFile);
  ~ScopeModuleTestFixtures ();

  private:

  ScopeModuleTestFixtures ();

  static boost::property_tree::ptree* s_ptree;
};

*/
