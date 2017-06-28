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

#include "DDvsMC_plotting.h"

using namespace std;

TH1F* GetDataDrivenHist (const string& filename, const string& sample)
{
  TString file = Form("/home/users/dpg/MT2AnalysisEdit/MyCode/DataDrivenHistExtraction/hists/%s.root", filename.c_str());
  TFile * tf = TFile::Open(file);
  TH1F* toReturn = (TH1F*) (tf->Get( ("h_"+sample).c_str() ))->Clone();
  toReturn->SetDirectory(0);
  toReturn->SetTitle( Form("Data Driven %s for %s M_{T2}", sample.c_str(), filename.c_str()) );
  tf->Close();
  return toReturn;
}

TH1F* GetMonteCarloHist (const string& filename, const string& SR_key)
{
  TString file = Form("/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/output/%s.root", filename.c_str());
  TFile * tf = TFile::Open(file);
  TH1F* toReturn = (TH1F*) (tf->Get(SR_key.c_str()))->Clone();
  toReturn->SetDirectory(0);
  toReturn->SetTitle( Form("Monte Carlo %s SR %s M_{T2}", filename.c_str(), SR_key.c_str()) );
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
      TH1F* dd_qcd = GetDataDrivenHist(sr_file_dd[i], "qcd");    
      TH1F* mc_qcd = GetMonteCarloHist("qcd_ht", sr_key_mc[i]);
      mc_qcd->SetLineColor(kRed);
      TLegend * tl_qcd = new TLegend(x1, y1, x2, y2);
      tl_qcd->AddEntry(dd_qcd);
      tl_qcd->AddEntry(mc_qcd);
      
      TH1F* dd_ll = GetDataDrivenHist(sr_file_dd[i], "ll");
      TH1F* mc_ll = GetMonteCarloHist("lostlepton", sr_key_mc[i]);
      mc_ll->SetLineColor(kRed);
      TLegend * tl_ll = new TLegend(x1, y1, x2, y2);
      tl_ll->AddEntry(dd_ll);
      tl_ll->AddEntry(mc_ll);
      
      // need this workaround because 3UH does not exist for zinvFromDY
      TH1F* dd_zdy;
      if (i != 42)
	{
	  dd_zdy = GetDataDrivenHist(sr_file_dd[i], "zdy");
	}
      // need this workaround because 11L and the super signal regions 20+
      // do not exist for zinvFromGJ 
      TH1F* dd_zgj; 
      if (i != 17 && i < 50) 
	{
	  dd_zgj = GetDataDrivenHist(sr_file_dd[i], "zgj");
	  dd_zgj->SetLineColor(kGreen);
	}
      TH1F* mc_z = GetMonteCarloHist("zinv_ht", sr_key_mc[i]);

      mc_z->SetLineColor(kRed);
      TLegend * tl_z = new TLegend(x1, y1, x2, y2);
      if (i != 42) tl_z->AddEntry(dd_zdy);
      if (i != 17 && i < 50) tl_z->AddEntry(dd_zgj);
      tl_z->AddEntry(mc_z);

      c1.SetLogy(true);

      double MaxToSet, MinToSet;
      
      MaxToSet = max(mc_qcd->GetMaximum(), dd_qcd->GetMaximum());
      MinToSet = min(mc_qcd->GetMinimum(), dd_qcd->GetMinimum());
      mc_qcd->SetMaximum( 10 * MaxToSet );
      mc_qcd->SetMinimum( MinToSet > 0 ? MinToSet / 10 : 0.0001);
      mc_qcd->SetTitle( Form("QCD %s M_{T2} Distributions;M_{T2} (GeV);Count @ 35.9 fb^{-1}", sr_desc[i].c_str()));
      mc_qcd->Draw("E1");
      dd_qcd->Draw("E1 same");
      tl_qcd->Draw();
      c1.SaveAs( ("PNGs/qcd_estimates_"+sr_key_mc[i]+".png").c_str() );

      MaxToSet = max(mc_ll->GetMaximum(), dd_ll->GetMaximum());
      MinToSet = min(mc_ll->GetMinimum(), dd_ll->GetMinimum());
      mc_ll->SetMaximum( 10 * MaxToSet ); 
      mc_ll->SetMinimum( MinToSet > 0 ? MinToSet / 10 : 0.0001);
      mc_ll->SetTitle( Form("Lost Lepton %s M_{T2} Distributions;M_{T2} (GeV);Count @ 35.9 fb^{-1}", sr_desc[i].c_str()));
      mc_ll->Draw("E1");
      dd_ll->Draw("E1 same");
      tl_ll->Draw();
      c1.SaveAs( ("PNGs/lostlep_estimates_"+sr_key_mc[i]+".png").c_str() );
      
      double zdy_max = 0.0, zgj_max = 0.0, zdy_min = FLT_MAX, zgj_min = FLT_MAX;
      if (i != 42) zdy_max = dd_zdy->GetMaximum();
      if (i != 17 && i < 50) zgj_max = dd_zgj->GetMaximum();
      MaxToSet = max( mc_z->GetMaximum(), max(zdy_max, zgj_max));
      MinToSet = min( mc_z->GetMinimum(), min(zdy_min, zgj_min));
      mc_z->SetMaximum( 10 * MaxToSet );
      mc_z->SetMinimum( MinToSet > 0 ? MinToSet / 10 : 0.0001);
      mc_z->SetTitle( Form("Z->#nu#nu %s M_{T2} Distributions;M_{T2} (GeV);Count @ 35.9 fb^{-1}", sr_desc[i].c_str()));
      mc_z->Draw("E1");
      // see comments above
      if (i != 42) dd_zdy->Draw("E1 same");
      if (i != 17 && i < 50) dd_zgj->Draw("E1 same");
      tl_z->Draw();
      c1.SaveAs( ("PNGs/zinv_estimates_"+sr_key_mc[i]+".png").c_str() );      

      // ratio plots
      c1.SetLogy( false );
      mc_qcd->Divide(dd_qcd);
      mc_qcd->SetMaximum( 3.0 );
      mc_qcd->SetMinimum( 0 );
      mc_qcd->SetTitle( Form("QCD %s M_{T2} Ratio;M_{T2} (GeV);MC/DD", sr_desc[i].c_str() ));
      mc_qcd->Draw("E1");
      c1.SaveAs( ("PNGs/qcd_ratio_"+sr_key_mc[i]+".png").c_str() );
      
      mc_ll->Divide(dd_ll);
      mc_ll->SetMaximum( 3.0 );
      mc_ll->SetMinimum( 0 );
      mc_ll->SetTitle( Form("Lost Lepton %s M_{T2} Ratio;M_{T2} (GeV);MC/DD", sr_desc[i].c_str()));
      mc_ll->Draw("E1");
      c1.SaveAs( ("PNGs/lostlep_ratio_"+sr_key_mc[i]+".png").c_str() );

      mc_z->SetMaximum(3.0);
      mc_z->SetMinimum(0);
      if (i != 42)
	{
	  TH1F * mc_z1 = (TH1F*) mc_z->Clone();
	  mc_z1->Divide(dd_zdy);
	  mc_z1->SetTitle( Form("Z->#nu#nu %s M_{T2} Ratio;M_{T2} (GeV);MC/DD (DY)", sr_desc[i].c_str()));
	  mc_z1->Draw("E1");
	  c1.SaveAs( ("PNGs/zinv_ratio_dy_"+sr_key_mc[i]+".png").c_str() );
	}
      if (i != 17 && i < 50)
	{
	  TH1F* mc_z2 = (TH1F*) mc_z->Clone();
	  mc_z2->Divide(dd_zgj);
	  mc_z2->SetTitle( Form("Z->#nu#nu %s M_{T2} Ratio;M_{T2} (GeV);MC/DD (GJ)", sr_desc[i].c_str()));
	  mc_z2->Draw("E1");
	  c1.SaveAs( ("PNGs/zinv_ratio_gj_"+sr_key_mc[i]+".png").c_str() );
	}
      
    }
  
}
