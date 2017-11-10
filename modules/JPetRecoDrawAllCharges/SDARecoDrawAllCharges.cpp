/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file SDARecoDrawAllCharges.cpp
 */

#include <sstream>
#include <THStack.h>
#include <TLegend.h>
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"
#include "SDARecoDrawAllCharges.h"
using namespace std;
SDARecoDrawAllCharges::SDARecoDrawAllCharges(const char* name): JPetUserTask(name) {}
SDARecoDrawAllCharges::~SDARecoDrawAllCharges() {}

bool SDARecoDrawAllCharges::init()
{
  const auto& paramBank = getParamBank();
  fNumberOfPMTs = paramBank.getPMsSize();
  cout << "Found " << fNumberOfPMTs << " PMTs in paramBank" << endl;
  for (const auto& id_pm_pair : getParamBank().getPMs() ) {
    fIDs.push_back( id_pm_pair.first);
    std::vector<double> k;
    fCharges[id_pm_pair.first] = k;
  }
  return true;
}

bool SDARecoDrawAllCharges::exec()
{
  if (auto signal = dynamic_cast<const JPetRecoSignal* const>(fEvent))
    fCharges[signal->getPM().getID()].push_back(signal->getCharge());
  return true;
}

bool SDARecoDrawAllCharges::terminate()
{
  auto c1 = new TCanvas();
  //looking for max and min value for all offsets
  double maximum = -1.e20;
  double minimum = 1.e20;
  for (const auto& id_vec_pair : fCharges ) {
    double local_min = JPetRecoSignalTools::min( id_vec_pair.second );
    double local_max = JPetRecoSignalTools::max( id_vec_pair.second );
    if ( local_max > maximum) maximum = local_max;
    if ( local_min < minimum) minimum = local_min;
  }

  maximum = maximum + maximum * 0.1;
  minimum = minimum - minimum * 0.1;
  //========= I don't understand this place (Rundel) ======
  maximum = 120;
  minimum = 0;
  // ======================================================
  if (minimum < -100)
    minimum = -100;
  int bins = maximum - minimum;
  if (bins < 0)
    bins *= -1;
  for (const auto& id_vec_pair : fCharges ) {
    stringstream ss;
    ss << id_vec_pair.first;
    string title = "Charge for PMT" + ss.str();
    fChargeHistos[id_vec_pair.first] = new TH1F( title.c_str(), title.c_str() , bins, minimum, maximum );
    for (size_t i = 0; i < fCharges[id_vec_pair.first].size(); ++i)
      fChargeHistos[id_vec_pair.first]->Fill(fCharges[id_vec_pair.first][i], 1);
  }
  auto stack = new THStack("hs1", ";Charge [pC];Counts");
  int i = 1;
  for (const auto& id_histo_pair : fChargeHistos) {
    id_histo_pair.second->GetXaxis()->SetTitle("Charge [pC]");
    id_histo_pair.second->GetYaxis()->SetTitle("Counts");
    id_histo_pair.second->SetLineWidth(2);
    id_histo_pair.second->SetLineColor(i++);
    stack->Add(id_histo_pair.second);
  }
  stack->Draw("nostack");
  auto leg = c1->BuildLegend();
  leg->Draw();
  string title = "Charges.root";
  c1->SaveAs( title.c_str() );
  title = "Charges.png";
  c1->SaveAs( title.c_str() );
  delete c1; // I propose to use shared_ptr here (Rundel)
  delete stack;
  return true;
}

