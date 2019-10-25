/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetScopeLoaderFixtures.h
 */

#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetScopeTask/JPetScopeTaskUtils.h"
#include "./JPetScopeLoader/JPetScopeLoader.h"
#include "./JPetRecoSignal/JPetRecoSignal.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include "./JPetScopeTask/JPetScopeTask.h"
#include "./JPetParamBank/JPetParamBank.h"
#include "./JPetReader/JPetReader.h"
#include <cstddef>
#include <cstdio>

const char* gTest_signal_filename = "unitTestData/JPetScopeLoaderTest/scope_files/0/C1_00003.txt";

struct reco_signal_generator {
public:
  reco_signal_generator ();
  ~reco_signal_generator ();
  int setup (const char*);
  int check_header (void (*unit_test_function) (int, int) = nullptr);
  int check_data (void (*unit_test_function) (float, float, float, float) = nullptr);

private:
  int m_segment_size;
  JPetRecoSignal m_reco_signal;
  FILE* m_file;
};

reco_signal_generator::reco_signal_generator () : m_file(nullptr) {}

reco_signal_generator::~reco_signal_generator ()
{
  if (m_file != nullptr) fclose (m_file);
}

int reco_signal_generator::setup (const char* filename)
{
  m_reco_signal = RecoSignalUtils::generateSignal (filename);
  m_file = fopen(filename, "r");
  return 0;
}

int reco_signal_generator::check_header (void (*unit_test_function) (int, int))
{
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

int reco_signal_generator::check_data (void (*unit_test_function) (float, float, float, float))
{
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
      (*unit_test_function) (time, m_reco_signal.getShape()[i].time,
        amplitude, m_reco_signal.getShape()[i].amplitude);
    }
  }
  return 0;
}

struct signal_generation_fixture : public reco_signal_generator {
public:
  signal_generation_fixture ();
  ~signal_generation_fixture ();
};

signal_generation_fixture::signal_generation_fixture (): reco_signal_generator() {
  reco_signal_generator::setup(gTest_signal_filename);
}

signal_generation_fixture::~signal_generation_fixture () {}

const char* gTest_root_filename = "test_file_test_0.reco.sig.root";

struct root_file_reader {
public:
  root_file_reader ();
  ~root_file_reader ();
  int setup (const char*);
  void check_tref_simple (void (*unit_test_function) (const void*) = nullptr);

private:
  JPetReader m_reader;
  JPetTreeHeader* m_header;
  JPetParamBank const* m_bank;
  JPetParamManager m_manager;
};

root_file_reader::root_file_reader ():
  m_reader(), m_header(nullptr), m_bank(nullptr), m_manager() {}

root_file_reader::~root_file_reader ()
{
  m_reader.closeFile();
  if (m_header != nullptr) {
    delete m_header;
    m_header = nullptr;
  }
  m_bank = nullptr;
}

int root_file_reader::setup (const char* filename)
{
  m_reader.openFileAndLoadData(filename);
  if (m_reader.isOpen()) {
    m_header = m_reader.getHeaderClone();
    m_manager.readParametersFromFile(&m_reader);
    m_bank = & m_manager.getParamBank();
  } else return -1;
  return 0;
}

void root_file_reader::check_tref_simple (void (*unit_test_function) (const void*))
{
  JPetRecoSignal& sig = reinterpret_cast <JPetRecoSignal&> (m_reader.getCurrentEvent());
  for (int i = 0; i < m_reader.getNbOfAllEvents(); ++i) {
    m_reader.nthEvent(i);
    if (unit_test_function != nullptr) {
      (*unit_test_function) (&(sig.getPM()));
    }
  }
}

struct tref_correctness_fixture: public root_file_reader {
public:
  tref_correctness_fixture();
  ~tref_correctness_fixture();
};

tref_correctness_fixture::tref_correctness_fixture () : root_file_reader()
{
  root_file_reader::setup(gTest_root_filename);
}

tref_correctness_fixture::~tref_correctness_fixture () {}
