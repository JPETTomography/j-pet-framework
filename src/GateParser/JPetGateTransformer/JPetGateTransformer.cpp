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
 *  @file JPetGateTransformer.cpp
 */

#include "JPetOptionsTools/JPetOptionsTools.h"
#include <JPetGateTransformer/JPetGateTransformer.h>
#include <JPetGeantParser/JPetGeantParserTools.h>
using namespace jpet_options_tools;

JPetGateTransformer::JPetGateTransformer(const char* name) : JPetTask(name) {}

bool JPetGateTransformer::init(const JPetParams& inParams)
{
  INFO("GateTransformer started.");
  fOptions = inParams.getOptions();

  return true;
}

bool JPetGateTransformer::run(const JPetDataInterface&)
{
  auto inFile = getInputFile(fOptions);
  JPetGateTreeReader::DetectorGeometry geom = JPetGateTreeReader::DetectorGeometry::ThreeLayers;
  auto outputPath = getOutputPath(fOptions);
  if (outputPath == "")
  {
    outputPath = "./";
  }

  return transformTree(inFile, outputPath, geom);
}


void JPetGateTransformer::saveHits()
{
  INFO("[#]  JPetGateParser::saveHits");
  for (const auto& hit : fStoredHits)
  {
    fOutputEvents->add<JPetHit>(hit);
  }

  fStoredHits.clear();
}

void JPetGateTransformer::processGateHit(GateHit* gate_hit)
{
  if (fLastEventID != gate_hit->event_id)
  {
    fTimeShift = getNextTimeShift();
    fLastEventID = gate_hit->event_id;
  }

  JPetHit hit;

  JPetScin& scin = getParamBank().getScintillator(gate_hit->sci_id);
  hit.setScintillator(scin);
  hit.setBarrelSlot(scin.getBarrelSlot());

  /// Nonsmeared values
  auto scinID = gate_hit->sci_id;
  auto posZ = gate_hit->posz;
  auto energy = gate_hit->edep * 1000.0;
  auto time = gate_hit->time * 1e6 + fTimeShift;

  /// Smeared values
  hit.setEnergy(fExperimentalParametrizer.addEnergySmearing(scinID, posZ, energy, time));
  // adjust to time window and smear
  hit.setTime(fExperimentalParametrizer.addTimeSmearing(scinID, posZ, energy, time));
  auto radius = getParamBank().getScintillator(scinID).getBarrelSlot().getLayer().getRadius();
  auto theta = TMath::DegToRad() * getParamBank().getScintillator(hit.getScintillator().getID()).getBarrelSlot().getTheta();
  hit.setPosX(radius * std::cos(theta));
  hit.setPosY(radius * std::sin(theta));
  hit.setPosZ(fExperimentalParametrizer.addZHitSmearing(scinID, posZ, energy, time));

  if (JPetGeantParserTools::isHitReconstructed(hit, fExperimentalThreshold))
  {
    saveReconstructedHit(hit);
  }
}

void JPetGateTransformer::saveReconstructedHit(JPetHit recHit) { fStoredHits.push_back(recHit); }

bool JPetGateTransformer::terminate(JPetParams& outParams)
{
  OptsStrAny new_opts;
  // setOutputFileType(new_opts, "hld");
  // auto outputFile =
  // getOutputPath(fOptions)
  //+ JPetCommonTools::stripFileNameSuffix(getInputFile(fOptions));
  // setOutputFile(new_opts, outputFile);

  // if (isOptionSet(fOptions, "firstEvent_int") && isOptionSet(fOptions, "lastEvent_int")) {
  // if (getOptionAsInt(fOptions, "firstEvent_int") != -1 && getOptionAsInt(fOptions, "lastEvent_int") != -1) {
  // setResetEventRangeOption(new_opts, true);
  //}
  //}

  // outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  // INFO(Form(
  //"GateTransformer finished, unzipped file name: %s", outputFile.c_str()
  //));
  return true;
}

bool JPetGateTransformer::transformTree(const std::string& inFile, const std::string& outFile, JPetGateTreeReader::DetectorGeometry geom)
{
  JPetGateTreeWriter w(outFile);
  JPetGateTreeReader r(inFile, geom);
  while (r.read())
  {
    GateHit* p_gh = r.get();
    if (p_gh != nullptr)
      w.write(*p_gh);
  }
  r.close();
  w.close();
  return true;
}

bool JPetGateTransformer::transformTree2(const std::string& inFile, const std::string& outFile, JPetGateTreeReader::DetectorGeometry geom)
{

  // JPetGateTreeWriter w(outFile);
  JPetGateTreeReader r(inFile, geom);
  while (r.read())
  {
    GateHit* p_gh = r.get();
    if (!p_gh)
      continue;
    processGateHit(p_gh);
    if (isTimeWindowFull())
    {
      saveHits();
      clearTimeDistoOfDecays();
      // std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(fSimulatedActivity, fMinTime, fMaxTime);
    }
  }
  r.close();
  // w.close();
  // JPetGateTreeWriter w(outFile);
  // JPetGateTreeReader r(inFile, geom);
  // while (r.read())
  //{
  // GateHit* p_gh = r.get();
  // if (p_gh != nullptr)
  // w.write(*p_gh);
  //}
  // r.close();
  // w.close();
  return true;
}

JPetGateTreeWriter::JPetGateTreeWriter(const std::string& outFileName) : fOutputFileName(outFileName)
{
  fFile = new TFile(fOutputFileName.c_str() /*"data.mcGate.root"*/, "RECREATE");
  fTree = new TTree("T", "T");
  fTree->Branch("GHit", &fGateHit);
}

void JPetGateTreeWriter::write(GateHit gh)
{
  fGateHit->copy(gh);
  fTree->Fill();
}

void JPetGateTreeWriter::close()
{
  fFile->Write();
  fFile->Close();
}

JPetGateTreeReader::JPetGateTreeReader(const std::string& inFile, JPetGateTreeReader::DetectorGeometry geom)
    : fInputFileName(inFile), fDetectorGeometry(geom)
{
  fFile = new TFile(fInputFileName.c_str(), "READ");
  fTree = dynamic_cast<TTree*>(fFile->Get("Hits"));
  entries = fTree->GetEntries();
  fTree->SetBranchAddress("PDGEncoding", &pdg, &b_pdg);
  fTree->SetBranchAddress("trackID", &track_id, &b_track_id);
  fTree->SetBranchAddress("parentID", &parent_id, &b_parent_id);
  fTree->SetBranchAddress("time", &time, &b_time);
  fTree->SetBranchAddress("eventID", &event_id, &b_event_id);
  fTree->SetBranchAddress("posX", &posx, &b_posx);
  fTree->SetBranchAddress("posY", &posy, &b_posy);
  fTree->SetBranchAddress("posZ", &posz, &b_posz);
  fTree->SetBranchAddress("edep", &edep, &b_edep);
  fTree->SetBranchAddress("processName", process_name, &b_process_name);
  fTree->SetBranchAddress("sourcePosX", &sourcex, &b_sourcex);
  fTree->SetBranchAddress("sourcePosY", &sourcey, &b_sourcey);
  fTree->SetBranchAddress("sourcePosZ", &sourcez, &b_sourcez);
  fTree->SetBranchAddress("volumeID", &volID, &b_volID);
}

bool JPetGateTreeReader::read()
{
  if (entry_index < entries)
    fTree->GetEntry(entry_index);
  else
    return false;
  ++entry_index;
  return true;
}

GateHit* JPetGateTreeReader::get()
{
  bool is_ok = parent_id == 0;
  is_ok = is_ok && pdg == 22;
  is_ok = is_ok && std::string(process_name) == "compt";
  if (!is_ok)
    return nullptr;
  ++counter;
  gate_hit.track_id = track_id;
  gate_hit.event_id = event_id;
  gate_hit.edep = edep;
  gate_hit.time = time;
  gate_hit.posx = posx / 10.0; // mm --> cm
  gate_hit.posy = posy / 10.0;
  gate_hit.posz = posz / 10.0;
  gate_hit.sourcex = sourcex;
  gate_hit.sourcey = sourcey;
  gate_hit.sourcez = sourcez;
  gate_hit.sci_id = getScintillatorId(volID[1], volID[2]);
  return &gate_hit;
}

void JPetGateTreeReader::close()
{
  fFile->Close();
  delete fFile;
  std::cout << counter << std::endl;
}


int JPetGateTreeReader::getScintillatorId(int volID1, int volID2) const
{
  switch (fDetectorGeometry)
  {
  case DetectorGeometry::ThreeLayers:
    return 1 + volID1;
  case DetectorGeometry::TwentyFourModules:
    return 201 + volID1 * 13 + volID2;
  default:
    return 0;
  };
}

unsigned int JPetGateTransformer::getNumberOfDecaysInWindow() const { return fTimeDistroOfDecays.size(); }

float JPetGateTransformer::getNextTimeShift()
{
  float t = fTimeDistroOfDecays[fCurrentIndexTimeShift];
  fCurrentIndexTimeShift++;
  return t;
}

void JPetGateTransformer::clearTimeDistoOfDecays()
{
  fCurrentIndexTimeShift = 0;
  fTimeDiffDistro.clear();
  fTimeDistroOfDecays.clear();
}

bool JPetGateTransformer::isTimeWindowFull() const
{
  if (fCurrentIndexTimeShift >= getNumberOfDecaysInWindow())
  {
    return true;
  }
  else
  {
    return false;
  }
}

unsigned long JPetGateTransformer::getOriginalSeed() const { return fSeed; }

const JPetParamBank& JPetGateTransformer::getParamBank()
{
  DEBUG("JPetUserTask");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
}
