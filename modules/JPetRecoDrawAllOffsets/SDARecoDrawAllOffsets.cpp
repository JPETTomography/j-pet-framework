#include "./SDARecoDrawAllOffsets.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"

//standard constructor
SDARecoDrawAllOffsets::SDARecoDrawAllOffsets(const char* name, const char* description): JPetTask(name, description)
{
}

//no specific destructor needed
SDARecoDrawAllOffsets::~SDARecoDrawAllOffsets()
{
}

void SDARecoDrawAllOffsets::init()
{
    const JPetParamBank& paramBank = getParamBank();
    fNumberOfPMTs = paramBank.getPMsSize();
    std::cout<<"Found " << fNumberOfPMTs << " PMTs in paramBank\n";

    for(unsigned int i = 0; i < fNumberOfPMTs; i++)
    {   
        fIDs.push_back( paramBank.getPM(i).getID() );
        std::vector<double> k;
        fOffsets.push_back( k); 
    }   
    

}

void SDARecoDrawAllOffsets::exec()
{
  // Cast data from the entry into JPetRecoSignal
  const JPetRecoSignal& signal = (JPetRecoSignal&)(*getEvent());

    for(unsigned int j = 0; j < fNumberOfPMTs; j++)
    {
        if( (signal.getPM().getID()) == fIDs[j] )
        {
          //get offset and fill
          fOffset = signal.getOffset();
          fOffsets[j].push_back(fOffset);
          break;
        }
    }
}

void SDARecoDrawAllOffsets::terminate()
{

    TCanvas* c1 = new TCanvas();
    std::vector<double> minimums, maximums;
    //looking for max and min value for all offsets
    for ( unsigned int j = 0; j < fNumberOfPMTs; j++ )
    {
        minimums.push_back( JPetRecoSignalTools::min( fOffsets[j] ) );
        maximums.push_back( JPetRecoSignalTools::max( fOffsets[j] ) );
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
        std::string title = "Offset for PMT" + ss.str();
        fOffsetHistos.push_back(new TH1F( title.c_str(), title.c_str() , bins, minimum, maximum ));
             ss.str( std::string() );
              ss.clear();
    }

    //filling histos
    for( unsigned int j = 0; j < fNumberOfPMTs; j++ )
    {
        for(unsigned int i = 0; i < fOffsets[j].size(); ++i)
        {
            fOffsetHistos[j]->Fill(fOffsets[j][i],1);
        }
    }

    //looking for tallest histo
    unsigned int tallest = 0;
    int tallestHeight = (fOffsetHistos[0]->GetBinContent( fOffsetHistos[0]->GetMaximumBin() ) );
    for(unsigned int j = 1; j < fNumberOfPMTs; j++)
    {
        if( fOffsetHistos[j]->GetBinContent( fOffsetHistos[j]->GetMaximumBin() ) > tallestHeight )
        {
            tallest = j;
            tallestHeight = fOffsetHistos[j]->GetBinContent(fOffsetHistos[j]->GetMaximumBin());
        }
    }

    //plotting tallest histo
    fOffsetHistos[tallest]->GetXaxis()->SetTitle("Charge [pC]");
    fOffsetHistos[tallest]->GetYaxis()->SetTitle("Counts");
    fOffsetHistos[tallest]->Draw();
    fOffsetHistos[tallest]->SetLineWidth(4);

    TLegend* legend = new TLegend(0.4,0.6,0.89,0.89);
        legend->AddEntry(fOffsetHistos[tallest], fOffsetHistos[tallest]->GetTitle(),"l");
    //plotting the rest
    for(unsigned int i = 0; i < fOffsetHistos.size(); i++)
    {
        if(i == tallest)
            continue;
        fOffsetHistos[i]->SetLineWidth(4);
        fOffsetHistos[i]->SetLineColor(i+1);
//      fOffsetHistos[i]->Draw("same");

        legend->AddEntry(fOffsetHistos[i], fOffsetHistos[i]->GetTitle(),"l");

    }

//  legend->Draw();

        std::string title = "fOffsetsForAll.root";

        c1->SaveAs( title.c_str() );

}

