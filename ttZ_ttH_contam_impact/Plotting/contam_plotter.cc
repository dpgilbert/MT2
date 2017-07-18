#include <iostream>

#include "TDirectory.h"
#include "TTreeCache.h"
#include "TMath.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TStyle.h"

#include "../../../CORE/Tools/utils.h"

#include "contam_plotting.h"

using namespace std;

TH1F* GetHiggsHist (const string& filename, const string& SR_key)
{
  TString file = "../ttz_mg_lo.root";
  TFile * tf = TFile::Open(file);
  TH1F* toReturn = (TH1F*) (tf->Get(SR_key.c_str()))->Clone();
  toReturn->SetDirectory(0);
  toReturn->SetTitle( Form("Monte Carlo ttZ without Higgs, SR %s", SR_key.c_str()) );
  toReturn->Scale(35.9); // 35.9 fb^-1
  tf->Close();
  return toReturn;
}

TH1F* GetFullHist (const string& filename, const string& SR_key)
{
  TString file = "/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/output/CleanSkim/ttz_mg_lo.root";
  TFile * tf = TFile::Open(file);
  TH1F* toReturn = (TH1F*) (tf->Get(SR_key.c_str()))->Clone();
  toReturn->SetDirectory(0);
  toReturn->SetTitle( Form("Monte Carlo ttZ including Higgs > #tau#tau, SR %s", SR_key.c_str()) );
  toReturn->Scale(35.9); // 35.9 fb^-1
  tf->Close();
  return toReturn;
}

int main (int argc, char ** argv)
{
  string sr_key_mc [63] = { "1VL", "2VL", "3VL", "12VL", "13VL", "14VL", "15VL",
		       "1L", "2L", "3L", "4L", "5L", "6L", "7L", "8L", "9L", "10L", "11L",
		       "1M", "2M", "3M", "4M", "5M", "6M", "7M", "8M", "9M", "10M", "11M",
		       "1H", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "11H",
		       "1UH", "2UH", "3UH", "4UH", "5UH", "6UH", "7UH", "8UH", "9UH", "10UH", "11UH",
		       "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};

  string sr_file_dd [63] = {"HT250to450_j2to3_b0",
			    "HT250to450_j2to3_b1",
			    "HT250to450_j2to3_b2",
			    "HT250to450_j4toInf_b0",
			    "HT250to450_j4toInf_b1",
			    "HT250to450_j4toInf_b2",
			    "HT250to450_j2toInf_b3toInf",			    

			    "HT450to575_j2to3_b0",
			    "HT450to575_j2to3_b1",
			    "HT450to575_j2to3_b2",
			    "HT450to575_j4to6_b0",
			    "HT450to575_j4to6_b1",
			    "HT450to575_j4to6_b2",
			    "HT450to575_j7toInf_b0",
			    "HT450to575_j7toInf_b1",
			    "HT450to575_j7toInf_b2",
			    "HT450to575_j2to6_b3toInf",
			    "HT450to575_j7toInf_b3toInf",

			    "HT575to1000_j2to3_b0",
			    "HT575to1000_j2to3_b1",
			    "HT575to1000_j2to3_b2",
			    "HT575to1000_j4to6_b0",
			    "HT575to1000_j4to6_b1",
			    "HT575to1000_j4to6_b2",
			    "HT575to1000_j7toInf_b0",
			    "HT575to1000_j7toInf_b1",
			    "HT575to1000_j7toInf_b2",
			    "HT575to1000_j2to6_b3toInf",
			    "HT575to1000_j7toInf_b3toInf",

			    "HT1000to1500_j2to3_b0",
			    "HT1000to1500_j2to3_b1",
			    "HT1000to1500_j2to3_b2",
			    "HT1000to1500_j4to6_b0",
			    "HT1000to1500_j4to6_b1",
			    "HT1000to1500_j4to6_b2",
			    "HT1000to1500_j7toInf_b0",
			    "HT1000to1500_j7toInf_b1",
			    "HT1000to1500_j7toInf_b2",
			    "HT1000to1500_j2to6_b3toInf",
			    "HT1000to1500_j7toInf_b3toInf",

			    "HT1500toInf_j2to3_b0",
			    "HT1500toInf_j2to3_b1",
			    "HT1500toInf_j2to3_b2",
			    "HT1500toInf_j4to6_b0",
			    "HT1500toInf_j4to6_b1",
			    "HT1500toInf_j4to6_b2",
			    "HT1500toInf_j7toInf_b0",
			    "HT1500toInf_j7toInf_b1",
			    "HT1500toInf_j7toInf_b2",
			    "HT1500toInf_j2to6_b3toInf",
			    "HT1500toInf_j7toInf_b3toInf",

			    "HT1000toInf_j2toInf",
			    "HT1500toInf_j2toInf",
			    "HT1000toInf_j4toInf",
			    "HT1500toInf_j4toInf",
			    "HT1000toInf_j7toInf",
			    "HT1500toInf_j7toInf",
			    "HT1000toInf_j2toInf_b2toInf",
			    "HT1500toInf_j2toInf_b2toInf",
			    "HT1000toInf_j2toInf_b3toInf",
			    "HT1500toInf_j2toInf_b3toInf",
			    "HT1000toInf_j7toInf_b3toInf"
			    "HT1500toInf_j7toInf_b3toInf"
  };
			    
  string sr_desc [63] = { "N_{jets} = [2, 4), N_{bjets} = 0, H_{T} = [250, 450), MET >= 250", "N_{jets} = [2, 4), N_{bjets} = 1, H_{T} = [250, 450), MET >= 250", "N_{jets} = [2, 4), N_{bjets} = 2, H_{T} = [250, 450), MET >= 250", "H_{T} = [250, 450), MET >= 250", "H_{T} = [250, 450), MET >= 250", "H_{T} = [250, 450), MET >= 250", "N_{jets} >= 2, N_{bjets} >= 3, H_{T} = [250, 450), MET >= 250",
		       "N_{jets} = [2, 4), N_{bjets} = 0, H_{T} = [450, 575), MET >= 250", "N_{jets} = [2, 4), N_{bjets} = 1, H_{T} = [450, 575), MET >= 250", "N_{jets} = [2, 4), N_{bjets} = 2, H_{T} = [450, 575), MET >= 250", "N_{jets} = [4, 7), N_{bjets} = 0, H_{T} = [450, 575), MET >= 250", "N_{jets} = [4, 7), N_{bjets} = 1, H_{T} = [450, 575), MET >= 250", "N_{jets} = [4, 7), N_{bjets} = 2, H_{T} = [450, 575), MET >= 250", "N_{jets} >= 7, N_{bjets} = 0, H_{T} = [450, 575), MET >= 250", "N_{jets} >= 7, N_{bjets} = 1, H_{T} = [450, 575), MET >= 250", "N_{jets} >= 7, N_{bjets} = 2, H_{T} = [450, 575), MET >= 250", "N_{jets} = [2, 7), N_{bjets} >= 3, H_{T} = [450, 575), MET >= 250", "N_{jets} >= 7, N_{bjets} >= 3, H_{T} = [450, 575), MET >= 250",
		       "N_{jets} = [2, 4), N_{bjets} = 0, H_{T} = [575, 1000), MET >= 250", "N_{jets} = [2, 4), N_{bjets} = 1, H_{T} = [575, 1000), MET >= 250", "N_{jets} = [2, 4), N_{bjets} = 2, H_{T} = [575, 1000), MET >= 250", "N_{jets} = [4, 7), N_{bjets} = 0, H_{T} = [575, 1000), MET >= 250", "N_{jets} = [4, 7), N_{bjets} = 1, H_{T} = [575, 1000), MET >= 250", "N_{jets} = [4, 7), N_{bjets} = 2, H_{T} = [575, 1000), MET >= 250", "N_{jets} >= 7, N_{bjets} = 0, H_{T} = [575, 1000), MET >= 250", "N_{jets} >= 7, N_{bjets} = 1, H_{T} = [575, 1000), MET >= 250", "N_{jets} >= 7, N_{bjets} = 2, H_{T} = [575, 1000), MET >= 250", "N_{jets} = [2, 7), N_{bjets} >= 3, H_{T} = [575, 1000), MET >= 250", "N_{jets} >= 7, N_{bjets} >= 3, H_{T} = [575, 1000), MET >= 250",
		       "N_{jets} = [2, 4), N_{bjets} = 0, H_{T} = [1000, 1500), MET >= 30", "N_{jets} = [2, 4), N_{bjets} = 1, H_{T} = [1000, 1500), MET >= 30", "N_{jets} = [2, 4), N_{bjets} = 2, H_{T} = [1000, 1500), MET >= 30", "N_{jets} = [4, 7), N_{bjets} = 0, H_{T} = [1000, 1500), MET >= 30", "N_{jets} = [4, 7), N_{bjets} = 1, H_{T} = [1000, 1500), MET >= 30", "N_{jets} = [4, 7), N_{bjets} = 2, H_{T} = [1000, 1500), MET >= 30", "N_{jets} >= 7, N_{bjets} = 0, H_{T} = [1000, 1500), MET >= 30", "N_{jets} >= 7, N_{bjets} = 1, H_{T} = [1000, 1500), MET >= 30", "N_{jets} >= 7, N_{bjets} = 2, H_{T} = [1000, 1500), MET >= 30", "N_{jets} = [2, 7), N_{bjets} >= 3, H_{T} = [1000, 1500), MET >= 30", "N_{jets} >= 7, N_{bjets} >= 3, H_{T} = [1000, 1500), MET >= 30",
		       "N_{jets} = [2, 4), N_{bjets} = 0, H_{T} >= 1500, MET >= 30", "N_{jets} = [2, 4), N_{bjets} = 1, H_{T} >= 1500, MET >= 30", "N_{jets} = [2, 4), N_{bjets} = 2, H_{T} >= 1500, MET >= 30", "N_{jets} = [4, 7), N_{bjets} = 0, H_{T} >= 1500, MET >= 30", "N_{jets} = [4, 7), N_{bjets} = 1, H_{T} >= 1500, MET >= 30", "N_{jets} = [4, 7), N_{bjets} = 2, H_{T} >= 1500, MET >= 30", "N_{jets} >= 7, N_{bjets} = 0, H_{T} >= 1500, MET >= 30", "N_{jets} >= 7, N_{bjets} = 1, H_{T} >= 1500, MET >= 30", "N_{jets} >= 7, N_{bjets} = 2, H_{T} >= 1500, MET >= 30", "N_{jets} = [2, 7), N_{bjets} >= 3, H_{T} >= 1500, MET >= 30", "N_{jets} >= 7, N_{bjets} >= 3, H_{T} >= 1500, MET >= 30",
		       "N_{jets} >= 2, HT >= 1000, MET >= 30", 
			  "N_{jets} >= 2, H_{T} >= 1500, MET >= 30", 
			  "N_{jets} >= 4, H_{T} >= 1000, MET >= 30", 
			  "N_{jets} >= 4, H_{T} >= 1500, MET >= 30", 
			  "N_{jets} >= 7, H_{T} >= 1000, MET >= 30", 
			  "N_{jets} >= 7, H_{T} >= 1500, MET >= 30", 
			  "N_{jets} >= 2, N_{bjets} >= 2, H_{T} >= 1000, MET >= 30", 
			  "N_{jets} >= 2, N_{bjets} >= 2, H_{T} >= 1500, MET >= 30",  
			  "N_{jets} >= 2, N_{bjets} >= 3, H_{T} >= 1000, MET >= 30", 
			  "N_{jets} >= 2, N_{bjets} >= 3, H_{T} >= 1500, MET >= 30",  
			  "N_{jets} >= 7, N_{bjets} >= 3, H_{T} >= 1000, MET >= 30", 
			  "N_{jets} >= 7, N_{bjets} >= 3, H_{T} >= 1500, MET >= 30"};

  // turn off stat box
  gStyle->SetOptStat(0);
  TCanvas c1("c1_print_temp", "temp printer");
  Double_t x1 = 0.6, x2 = x1+0.35, y1 = 0.8, y2 = y1+0.1;
  for (unsigned int i = 0; i < 51; i++) // going to 51 rather than 63 for now until super signal region merging is implemented
    {
      TH1F* h_incl = GetFullHist("ttz_mg_lo", sr_key_mc[i]);    
      TH1F* h_excl = GetHiggsHist("ttz_mg_lo", sr_key_mc[i]);
      h_incl->SetLineColor(kRed);
      TLegend * tl_ = new TLegend(x1, y1, x2, y2);
      tl_->AddEntry(h_incl);
      tl_->AddEntry(h_excl);
      
      c1.SetLogy(true);

      h_incl->Draw("E1");
      h_excl->Draw("E1 same");
      tl_->Draw();
      c1.SaveAs( ("PNGs/contam_"+sr_key_mc[i]+".png").c_str() );

      // ratio plots
      c1.SetLogy( false );
      h_excl->SetMaximum(1.05);
      h_excl->SetMinimum(0.95);
      h_excl->Divide(h_incl);
      h_excl->SetTitle( Form("Ratio of ttH-Exclusive to Inclusivein %s;M_{T2} (GeV);ttZ / (ttZ + tt(H>#tau#tau))", sr_desc[i].c_str() ));
      h_excl->Draw("hist");
      c1.SaveAs( ("PNGs/ratio_"+sr_key_mc[i]+".png").c_str() );
      
    }
  
}
