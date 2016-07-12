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

#include "./SDARecoDrawAllCharges.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"
#include <THStack.h>

//standard constructor
SDARecoDrawAllCharges::SDARecoDrawAllCharges(const char* name, const char* description): JPetTask(name, description)
{
}

//no specific destructor needed
SDARecoDrawAllCharges::~SDARecoDrawAllCharges()
{
}

void SDARecoDrawAllCharges::init()
{
    const JPetParamBank& paramBank = getParamBank();
    fNumberOfPMTs = paramBank.getPMsSize();
    std::cout<<"Found " << fNumberOfPMTs << " PMTs in paramBank\n";

    for(auto & id_pm_pair : getParamBank().getPMs() ){
      fIDs.push_back( id_pm_pair.first);
      std::vector<double> k;
      fCharges[id_pm_pair.first] = k;
    }
    
}

void SDARecoDrawAllCharges::exec()
{
  // Cast data from the entry into JPetRecoSignal
  const JPetRecoSignal& signal = (JPetRecoSignal&)(*getEvent());
  
  fCharges[signal.getPM().getID()].push_back(signal.getCharge());
  
}

void SDARecoDrawAllCharges::terminate()
{
  TCanvas* c1 = new TCanvas();

  //looking for max and min value for all offsets  
  double maximum = -1.e20;
  double minimum = 1.e20;
  
  for ( auto & id_vec_pair : fCharges )
    {
      double local_min = JPetRecoSignalTools::min( id_vec_pair.second );
      double local_max = JPetRecoSignalTools::max( id_vec_pair.second );
      
      if( local_max > maximum) maximum = local_max;
      if( local_min < minimum) minimum = local_min;
    }
  
  maximum = maximum + maximum*0.1;
  minimum = minimum - minimum*0.1;
  
  maximum = 120;
  minimum = 0;
  
    if(minimum < -100)
      minimum = -100;
    
    int bins = maximum - minimum;

    if(bins<0)
        bins*=-1;
    
    //making vector of histos
    for ( auto & id_vec_pair : fCharges ){
      
      std::stringstream ss;
      ss << id_vec_pair.first;
      std::string title = "Charge for PMT" + ss.str();
      fChargeHistos[id_vec_pair.first] = new TH1F( title.c_str(), title.c_str() , bins, minimum, maximum );
      ss.str( std::string() );
      ss.clear();

    //filling histos
      for(unsigned int i = 0; i < fCharges[id_vec_pair.first].size(); ++i)
        {
	  fChargeHistos[id_vec_pair.first]->Fill(fCharges[id_vec_pair.first][i],1);
        }
      
    }
    
    THStack * stack = new THStack("hs1", ";Charge [pC];Counts");
    int i=1;
    for(auto & id_histo_pair : fChargeHistos){

      id_histo_pair.second->GetXaxis()->SetTitle("Charge [pC]");
      id_histo_pair.second->GetYaxis()->SetTitle("Counts");
      id_histo_pair.second->SetLineWidth(2);
      id_histo_pair.second->SetLineColor(i++);
      
      stack->Add(id_histo_pair.second);
    }

    stack->Draw("nostack");
    
    TLegend * leg = c1->BuildLegend();
    leg->Draw();
    
    std::string title = "Charges.root";
    
    c1->SaveAs( title.c_str() ); 

    title = "Charges.png";

    c1->SaveAs( title.c_str() ); 
    
    delete c1;
    delete stack;
}

