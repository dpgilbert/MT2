#include <iostream>

#include "TDirectory.h"
#include "TTreeCache.h"
#include "TMath.h"
#include "TH1.h"
#include "TFile.h"

#include "../../../CORE/Tools/utils.h"

#include "LostLepCombine.h"

using namespace std;

TH1F* GetHist (const string& filename, const string& SR_key)
{
  TString file = Form("/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/output/%s.root", filename.c_str());
  TFile * tf = TFile::Open(file);
  TH1F* toReturn = (TH1F*) (tf->Get(SR_key.c_str()))->Clone();
  toReturn->SetDirectory(0);
  tf->Close();
  return toReturn;
}

int main (int argc, char ** argv)
{
  string sr_key [63] = { "1VL", "2VL", "3VL", "12VL", "13VL", "14VL", "15VL",
			 "1L", "2L", "3L", "4L", "5L", "6L", "7L", "8L", "9L", "10L", "11L",
			 "1M", "2M", "3M", "4M", "5M", "6M", "7M", "8M", "9M", "10M", "11M",
			 "1H", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "11H",
			 "1UH", "2UH", "3UH", "4UH", "5UH", "6UH", "7UH", "8UH", "9UH", "10UH", "11UH",
			 "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};      		

  TFile tf ("lostlepton.root", "RECREATE");
  for (unsigned int i = 0; i < 63; i++)
    {
      TH1F* dy = GetHist("dyjetsll_ht", sr_key[i]);
      TH1F* st = GetHist("singletop", sr_key[i]);
      TH1F* ttdl = GetHist("ttdl", sr_key[i]);
      TH1F* ttsl = GetHist("ttsl", sr_key[i]);
      TH1F* ttg = GetHist("ttg", sr_key[i]);
      TH1F* tth = GetHist("tth", sr_key[i]);
      TH1F* ttw = GetHist("ttw_mg_lo", sr_key[i]);
      TH1F* ttz = GetHist("ttz_mg_lo", sr_key[i]);
      TH1F* wj1 = GetHist("wjets_ht100to200", sr_key[i]);
      TH1F* wj2 = GetHist("wjets_ht1200to2500", sr_key[i]);
      TH1F* wj3 = GetHist("wjets_ht200to400", sr_key[i]);
      TH1F* wj4 = GetHist("wjets_ht400to600", sr_key[i]);
      TH1F* wj5 = GetHist("wjets_ht600to800", sr_key[i]);
      TH1F* wj6 = GetHist("wjets_ht800to1200", sr_key[i]);
      TH1F* wj7 = GetHist("wjets_ht2500toInf", sr_key[i]);
      
      TH1F* lostlep = (TH1F*) dy->Clone();
      lostlep->Add(st);
      lostlep->Add(ttdl);
      lostlep->Add(ttsl);
      lostlep->Add(ttg);
      lostlep->Add(tth);
      lostlep->Add(ttw);
      lostlep->Add(ttz);
      lostlep->Add(wj1);
      lostlep->Add(wj2);
      lostlep->Add(wj3);
      lostlep->Add(wj4);
      lostlep->Add(wj5);
      lostlep->Add(wj6);
      lostlep->Add(wj7);
      string oldtitle = lostlep->GetTitle();
      lostlep->SetTitle( ("Lost Lepton "+oldtitle).c_str() );
      tf.cd();
      lostlep->Write();    
    }
  tf.Close();
}
