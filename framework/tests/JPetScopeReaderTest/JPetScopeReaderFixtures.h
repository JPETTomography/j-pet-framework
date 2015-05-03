#include "../../JPetScopeReader/JPetScopeReader.h"

#include <cstddef>
#include <cstdio>

#include "../../JPetParamBank/JPetParamBank.h"
#include "../../JPetParamManager/JPetParamManager.h"
#include "../../JPetReader/JPetReader.h"
#include "../../JPetRecoSignal/JPetRecoSignal.h"
#include "../../JPetTreeHeader/JPetTreeHeader.h"

// *********************************************************************** //
// ********            Generate Single JPetRecoSignal             ******** //
// *********************************************************************** //

const char* test_signal_filename = "scope_files/0/C1_00003.txt";

struct reco_signal_generator {
  
  public:
  
  reco_signal_generator ();
  ~reco_signal_generator ();

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

reco_signal_generator::reco_signal_generator () : m_file(nullptr) {
}

// *********************************************************************** //

reco_signal_generator::~reco_signal_generator () {

  if (m_file != nullptr) fclose (m_file);
}

// *********************************************************************** //

int reco_signal_generator::setup (const char* filename) {
  
  m_reco_signal = JPetScopeReader::generateSignal (filename);
  m_file = fopen(filename, "r");

  return 0;
}

// *********************************************************************** //

int reco_signal_generator::check_header (void (*unit_test_function) (int, int)) {
  
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

int reco_signal_generator::check_data (void (*unit_test_function) (float, float, float, float)) {
  
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

struct signal_generation_fixture : public reco_signal_generator {
  
  public:

  signal_generation_fixture ();
  ~signal_generation_fixture ();

};

// *********************************************************************** //

signal_generation_fixture::signal_generation_fixture () : reco_signal_generator() {
  reco_signal_generator::setup(test_signal_filename);
}

// *********************************************************************** //

signal_generation_fixture::~signal_generation_fixture () {
}

// *********************************************************************** //
// ********                 Open Single ROOT file                 ******** //
// *********************************************************************** //

const char* test_root_filename = "test_file.reco.sig.test.0.root";

struct root_file_reader {
  
  public:

  root_file_reader ();
  ~root_file_reader ();

  int setup (const char*);

  public:

  void check_tref_simple (void (*unit_test_function) (const void*) = nullptr);

  private:

  JPetReader m_reader;
  JPetTreeHeader* m_header;
  JPetParamBank const* m_bank;
  JPetParamManager m_manager;

};

// *********************************************************************** //

root_file_reader::root_file_reader () : m_reader(), m_header(nullptr), m_bank(nullptr), m_manager() {
}

// *********************************************************************** //

root_file_reader::~root_file_reader () {

  m_reader.closeFile();

  if (m_header != nullptr) {
    delete m_header;
    m_header = nullptr;
  }

  m_bank = nullptr;

}

// *********************************************************************** //

int root_file_reader::setup (const char* filename) {
  
  m_reader.openFile(filename);
  m_reader.readData("tree");

  if (m_reader.isOpen()) {

    m_header = m_reader.getHeaderClone();

    m_manager.readParametersFromFile(&m_reader);
    m_bank = & m_manager.getParamBank();

  }
  else return -1;
  
  return 0;
}

// *********************************************************************** //

void root_file_reader::check_tref_simple (void (*unit_test_function) (const void*)) {
  
  JPetRecoSignal& sig = reinterpret_cast <JPetRecoSignal&> (m_reader.getData());

  for (int i = 0; i < m_reader.getEntries(); ++i) {
    
    m_reader.getEntry(i);

    if (unit_test_function != nullptr) {
      (*unit_test_function) (&(sig.getPM()));
    }
  }

}

// *********************************************************************** //
// ********               TRef Correctness Fixture                ******** //
// *********************************************************************** //

struct tref_correctness_fixture : public root_file_reader {

  public:

  tref_correctness_fixture();
  ~tref_correctness_fixture();

};

// *********************************************************************** //

tref_correctness_fixture::tref_correctness_fixture () : root_file_reader() {
  root_file_reader::setup(test_root_filename);
}

// *********************************************************************** //

tref_correctness_fixture::~tref_correctness_fixture () {
}

// *********************************************************************** //

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
