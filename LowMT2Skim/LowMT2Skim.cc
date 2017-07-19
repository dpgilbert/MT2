// A looper to skim MCs for events passing selections

#include <iostream>

#include "../../CORE/Tools/utils.h"

#include "../../MT2CORE/mt2tree.h"

using namespace std;

int main (int argc, char ** argv)
{
  if (argc < 4)
    {
      cout << "Usage: ./LowMT2Skim <input_directory> <sample> <output_directory>" << endl;
      return 0;
    }

  TChain* chain = new TChain("mt2");
  TString inputs = Form("%s%s*.root", argv[1], argv[2]);
  chain->Add(inputs);

  
  // Skim

  TString output_name = Form("%s%s.root", argv[3], argv[2]);
  TFile * outfile = TFile::Open( output_name , "RECREATE" );
  
  // run on unskimmed babies to apply lower mt2 cut and no MET cut

  const char * njCut = "(nJet30 > 0)";
  const char * dphiCut = "(deltaPhiMin > 0.3)";
  const char * domCut = "(diffMetMht / met_pt < 0.5)";
  const char * lepVeto = "(nMuons10 + nElectrons10 + nPFLep5LowMT + nPFHad10LowMT == 0)";
  const char * mt2Cut = "(nJet30 < 2 || mt2 > 100)";

  const char * cleanCut1 = "(met_miniaodPt / met_caloPt <= 5.0)";
  const char * cleanCut2 = "(nJet200MuFrac50DphiMet == 0)";

  const char * selection_string = Form("%s && %s && %s && %s && %s && %s && %s", njCut, dphiCut, domCut, lepVeto, mt2Cut, cleanCut1, cleanCut2);

  TTree * skimmed = chain->CopyTree ( selection_string );
  skimmed->Write();
  outfile->Close();
}
