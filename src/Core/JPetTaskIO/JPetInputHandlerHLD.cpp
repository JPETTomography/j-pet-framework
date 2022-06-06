/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetInputHandlerHLD.cpp
 */

#include <TDirectory.h>
#include <TFile.h>
#include <TH1F.h>
#include <TString.h>
#include <bits/stdint-uintn.h>
#include <iostream>
#include <string>
#include <vector>

#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetLoggerInclude.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetParamBank/JPetParamBank.h"
#include "JPetTaskIO/JPetInputHandlerHLD.h"
#include "JPetTaskIO/JPetTaskIOTools.h"

#include "unpacker.hpp"

JPetInputHandlerHLD::JPetInputHandlerHLD() {}

bool JPetInputHandlerHLD::openInput(const char* inputFilename, const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();

  fFile.open(inputFilename, std::ios::in | std::ios::binary);

  if (!fFile)
  {
    ERROR(Form("Failed to open input file: %s", inputFilename));
    return false;
  }

  if (loadTDCCalib(params))
  {
    WARNING("Failed to load TDC nonlinearity calibration. Unpacker will proceed without calibration.");
  }
  else
  {
    if (!fTDCCalib.empty())
    {
      unpacker::set_tdc_calib(fTDCCalib);
    }
  }

  return nextEntry(); /// load first entry ready for `get_entry`
}

void JPetInputHandlerHLD::closeInput() { fFile.close(); }
TObject& JPetInputHandlerHLD::getEntry() { return fEntryData; }

bool JPetInputHandlerHLD::nextEntry()
{
  if (fEntryRange.currentEntry == fEntryRange.lastEntry)
  {
    return false;
  }
  fEntryRange.currentEntry++;

  int success = unpacker::get_time_window(fEntryData.fMetaData, fEntryData.fOriginalData, fEntryData.fFilteredData, fEntryData.fPreprocData, fFile);

  if (success == 0)
  {
    return false;
  }

  return true;
}

bool JPetInputHandlerHLD::setEntryRange(const jpet_options_tools::OptsStrAny& options)
{
  bool isOK = false;
  auto firstEntry = 0ll;
  auto lastEntry = 0ll;
  std::tie(isOK, firstEntry, lastEntry) = calculateEntryRange(options);
  if (!isOK)
  {
    ERROR("Some error occured in setEntryRange");
    return false;
  }
  fEntryRange.firstEntry = firstEntry;
  fEntryRange.lastEntry = lastEntry;
  fEntryRange.currentEntry = firstEntry;
  return true;
}

std::tuple<bool, long long, long long> JPetInputHandlerHLD::calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const
{
  auto totalEntries = 1000000000ll;
  // @todo: consider scanning the HLD file first to determine the number of time windows inside
  WARNING("Unpacker of the HLD files is not able to determine the total number of events. Progressbar display may not be reliable.");
  return JPetTaskIOTools::setUserLimits(options, totalEntries);
}

bool JPetInputHandlerHLD::loadTDCCalib(const JPetParams& params)
{
  using namespace jpet_options_tools;

  std::string pathToRootFile = "";
  if (isOptionSet(params.getOptions(), kTOTOffsetCalibKey))
  {
    pathToRootFile = getOptionAsString(params.getOptions(), kTOTOffsetCalibKey);
  }
  else
  {
    WARNING("Path to file with TDC nonlinearity calibrations was not set. Skipping TDC calibration.");
    return false;
  }

  TFile* calib_rootfile = new TFile(pathToRootFile.c_str(), "READ");
  if (!calib_rootfile->IsOpen())
  {
    WARNING(TString::Format("Unable to open file: %s. Skipping TDC calibration.", pathToRootFile.c_str()));
    return false;
  }

  int run_id = getRunNumber(params.getOptions());
  for (auto& channel : params.getParamManager()->getChannels(run_id))
  {

    uint32_t channel_no = channel.second->getID();
    uint32_t address = channel.second->getDataModule().getTBRNetAddress();
    uint32_t local_channel_no = channel_no - channel.second->getDataModule().getChannelsOffset();

    TH1F* corr_histo = dynamic_cast<TH1F*>(calib_rootfile->FindObjectAny(TString::Format("correction%d", channel_no)));
    if (corr_histo == nullptr)
    {
      WARNING(TString::Format("Missing TDC correction for channel %d", channel_no));
      continue;
    }

    std::vector<uint32_t> corr_vec(128);
    for (int i = 1; i < corr_histo->GetNbinsX(); ++i)
    {
      corr_vec[i - 1] = corr_histo->GetBinContent(i) * 1000.;
    }

    fTDCCalib[address][local_channel_no] = corr_vec;
  }

  // separately handle reference channels
  for (auto& dm : params.getParamManager()->getDataModules(run_id))
  {
    uint32_t address = dm.second->getTBRNetAddress();
    uint32_t local_channel_no = dm.second->getChannelsNumber() - 1;
    uint32_t channel_no = dm.second->getChannelsOffset() + local_channel_no;

    TH1F* corr_histo = dynamic_cast<TH1F*>(calib_rootfile->FindObjectAny(TString::Format("correction%d", channel_no)));
    if (corr_histo == nullptr)
    {
      WARNING(TString::Format("Missing TDC correction for channel %d", channel_no));
      continue;
    }

    std::vector<uint32_t> corr_vec(128);
    for (int i = 1; i < corr_histo->GetNbinsX(); ++i)
    {
      corr_vec[i - 1] = corr_histo->GetBinContent(i) * 1000.;
    }

    fTDCCalib[address][local_channel_no] = corr_vec;
  }
  
  calib_rootfile->Close();
  delete calib_rootfile;

  return true;
}
