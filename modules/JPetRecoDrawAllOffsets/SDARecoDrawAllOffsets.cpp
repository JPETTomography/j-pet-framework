
#include "./SDARecoDrawAllOffsets.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"
#include <sstream>
#include <TLegend.h>
using namespace std;
SDARecoDrawAllOffsets::SDARecoDrawAllOffsets(const char* name): JPetUserTask(name) {}
SDARecoDrawAllOffsets::~SDARecoDrawAllOffsets() {}
bool SDARecoDrawAllOffsets::init()
{
  const auto& paramBank = getParamBank();
  fNumberOfPMTs = paramBank.getPMsSize();
  cout << "Found " << fNumberOfPMTs << " PMTs in paramBank\n";
  for (size_t i = 0; i < fNumberOfPMTs; i++) {
    fIDs.push_back( paramBank.getPM(i).getID() );
    vector<double> k;
    fOffsets.push_back( k);
  }
  return true;
}

bool SDARecoDrawAllOffsets::exec()
{
  if (auto signal = dynamic_cast<const JPetRecoSignal* const>(fEvent))
    for (unsigned int j = 0; j < fNumberOfPMTs; j++)
      if ( (signal->getPM().getID()) == fIDs[j] ) {
        fOffset = signal->getOffset();
        fOffsets[j].push_back(fOffset);
        break;
      }
  return true;
}

bool SDARecoDrawAllOffsets::terminate()
{
  auto c1 = new TCanvas();
  vector<double> minimums, maximums;
  for ( unsigned int j = 0; j < fNumberOfPMTs; j++ ) {
    minimums.push_back( JPetRecoSignalTools::min( fOffsets[j] ) );
    maximums.push_back( JPetRecoSignalTools::max( fOffsets[j] ) );
  }
  double maximum = JPetRecoSignalTools::max( maximums );
  double minimum = JPetRecoSignalTools::min( minimums );
  maximum = maximum + maximum * 0.1;
  minimum = minimum - minimum * 0.1;
  //============ the same strange place again (Rundel)
  maximum = 150;
  minimum = 0;
  //==================
  if (minimum < -100)
    minimum = -100;

  int bins = maximum - minimum;
  bins /= 2;
  if (bins < 0)bins *= -1;
  for (size_t j = 0; j < fNumberOfPMTs; j++ ) {
    stringstream ss;
    ss << fIDs[j];
    string title = "Offset for PMT" + ss.str();
    fOffsetHistos.push_back(new TH1F( title.c_str(), title.c_str() , bins, minimum, maximum ));
  }
  for ( unsigned int j = 0; j < fNumberOfPMTs; j++ ) {
    for (unsigned int i = 0; i < fOffsets[j].size(); ++i) {
      fOffsetHistos[j]->Fill(fOffsets[j][i], 1);
    }
  }
  unsigned int tallest = 0;
  int tallestHeight = (fOffsetHistos[0]->GetBinContent( fOffsetHistos[0]->GetMaximumBin() ) );
  for (unsigned int j = 1; j < fNumberOfPMTs; j++) {
    if ( fOffsetHistos[j]->GetBinContent( fOffsetHistos[j]->GetMaximumBin() ) > tallestHeight ) {
      tallest = j;
      tallestHeight = fOffsetHistos[j]->GetBinContent(fOffsetHistos[j]->GetMaximumBin());
    }
  }
  fOffsetHistos[tallest]->GetXaxis()->SetTitle("Charge [pC]");
  fOffsetHistos[tallest]->GetYaxis()->SetTitle("Counts");
  fOffsetHistos[tallest]->Draw();
  fOffsetHistos[tallest]->SetLineWidth(4);

  auto legend = new TLegend(0.4, 0.6, 0.89, 0.89);
  legend->AddEntry(fOffsetHistos[tallest], fOffsetHistos[tallest]->GetTitle(), "l");
  for (unsigned int i = 0; i < fOffsetHistos.size(); i++) {
    if (i == tallest)continue;
    fOffsetHistos[i]->SetLineWidth(4);
    fOffsetHistos[i]->SetLineColor(i + 1);
    legend->AddEntry(fOffsetHistos[i], fOffsetHistos[i]->GetTitle(), "l");
  }
  string title = "fOffsetsForAll.root";
  c1->SaveAs( title.c_str() );
  return true;
}
