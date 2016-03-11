#include "./SDARecoDrawAllCharges.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"

ClassImp(SDARecoDrawAllCharges);


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

    for(unsigned int i = 0; i < fNumberOfPMTs; i++)
    {   
        fIDs.push_back( paramBank.getPM(i).getID() );
        std::vector<double> k;
        fCharges.push_back( k); 
    }   
    

}

void SDARecoDrawAllCharges::exec()
{
  // Cast data from the entry into JPetRecoSignal
  const JPetRecoSignal& signal = (JPetRecoSignal&)(*getEvent());

    for(unsigned int j = 0; j < fNumberOfPMTs; j++)
    {
        if( (signal.getPM().getID()) == fIDs[j] )
        {
          //get offset and fill
          fCharge = signal.getCharge();
          fCharges[j].push_back(fCharge);
          break;
        }
    }
}

void SDARecoDrawAllCharges::terminate()
{

    TCanvas* c1 = new TCanvas();
    std::vector<double> minimums, maximums;
    //looking for max and min value for all offsets
    for ( unsigned int j = 0; j < fNumberOfPMTs; j++ )
    {
        minimums.push_back( JPetRecoSignalTools::min( fCharges[j] ) );
        maximums.push_back( JPetRecoSignalTools::max( fCharges[j] ) );
    }
        double maximum = JPetRecoSignalTools::max( maximums );
        double minimum = JPetRecoSignalTools::min( minimums );

        maximum = maximum + maximum*0.1;
        minimum = minimum - minimum*0.1;

    maximum = 150;
    minimum = 0;

    if(minimum < -100)
        minimum = -100;

    int bins = maximum - minimum;
    bins /= 2;

    if(bins<0)
        bins*=-1;

    //making vector of histos
    for( unsigned int j = 0; j < fNumberOfPMTs; j++ )
    {
        std::stringstream ss;
        ss << fIDs[j];
        std::string title = "Charge for PMT" + ss.str();
        fChargeHistos.push_back(new TH1F( title.c_str(), title.c_str() , bins, minimum, maximum ));
             ss.str( std::string() );
              ss.clear();
    }

    //filling histos
    for( unsigned int j = 0; j < fNumberOfPMTs; j++ )
    {
        for(unsigned int i = 0; i < fCharges[j].size(); ++i)
        {
            fChargeHistos[j]->Fill(fCharges[j][i],1);
        }
    }

    //looking for tallest histo
    unsigned int tallest = 0;
    int tallestHeight = (fChargeHistos[0]->GetBinContent( fChargeHistos[0]->GetMaximumBin() ) );
    for(unsigned int j = 1; j < fNumberOfPMTs; j++)
    {
        if( fChargeHistos[j]->GetBinContent( fChargeHistos[j]->GetMaximumBin() ) > tallestHeight )
        {
            tallest = j;
            tallestHeight = fChargeHistos[j]->GetBinContent(fChargeHistos[j]->GetMaximumBin());
        }
    }

    //plotting tallest histo
    fChargeHistos[tallest]->GetXaxis()->SetTitle("Charge [pC]");
    fChargeHistos[tallest]->GetYaxis()->SetTitle("Counts");
    fChargeHistos[tallest]->Draw();
    fChargeHistos[tallest]->SetLineWidth(4);

    TLegend* legend = new TLegend(0.4,0.6,0.89,0.89);
        legend->AddEntry(fChargeHistos[tallest], fChargeHistos[tallest]->GetTitle(),"l");
    //plotting the rest
    for(unsigned int i = 0; i < fChargeHistos.size(); i++)
    {
        if(i == tallest)
            continue;
        fChargeHistos[i]->SetLineWidth(4);
        fChargeHistos[i]->SetLineColor(i+1);
//      fChargeHistos[i]->Draw("same");

        legend->AddEntry(fChargeHistos[i], fChargeHistos[i]->GetTitle(),"l");

    }

//  legend->Draw();

        std::string title = "fChargesForAll.root";

        c1->SaveAs( title.c_str() );

}

