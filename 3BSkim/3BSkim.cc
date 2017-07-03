// A looper to skim MCs for events passing selections

#include <iostream>

#include "TH1.h"

#include "../../CORE/Tools/utils.h"

#include "../../MT2CORE/mt2tree.h"

using namespace std;

int main (int argc, char ** argv)
{
  if (argc < 4)
    {
      cout << "Usage: ./3BSkim.exe <input_directory> <sample> <output_directory>" << endl;
      return 0;
    }

  TChain* chain = new TChain("mt2");
  TString inputs = Form("%s%s.root", argv[1], argv[2]);
  chain->Add(inputs);

  
  // Skim

  TString output_name = Form("%s%s.root", argv[3], argv[2]);
  TFile * outfile = TFile::Open( output_name , "RECREATE" );
  
  // run on skimmed babies, just looking for Bs

  const char * selection_string = "(nBJet20 > 2)";

  TTree * skimmed = chain->CopyTree ( selection_string );
  skimmed->Write();
  outfile->Close();
}
