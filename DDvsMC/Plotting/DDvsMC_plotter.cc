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

TH1F* GetDataDrivenHist (const string& filename, const string& SR_key)
{
  TString file = Form("/home/users/dpg/MT2Analysis_6_6_2017/MT2looper/output/first_run/%s.root", filename.c_str());
  TFile * tf = TFile::Open(file);
  TDirectoryFile * tdf = (TDirectoryFile *) tf->Get( ("sr"+SR_key).c_str());
  TH1F* toReturn = (TH1F*) (tdf->Get("h_mt2bins"))->Clone();
  toReturn->SetDirectory(0);
  toReturn->SetTitle( Form("Data Driven %s SR %s M_{T2}", filename.c_str(), SR_key.c_str()) );
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
  string sr_key [63] = { "1VL", "2VL", "3VL", "12VL", "13VL", "14VL", "15VL",
		       "1L", "2L", "3L", "4L", "5L", "6L", "7L", "8L", "9L", "10L", "11L",
		       "1M", "2M", "3M", "4M", "5M", "6M", "7M", "8M", "9M", "10M", "11M",
		       "1H", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "11H",
		       "1UH", "2UH", "3UH", "4UH", "5UH", "6UH", "7UH", "8UH", "9UH", "10UH", "11UH",
		       "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
			

  // turn off stat box
  gStyle->SetOptStat(0);
  TCanvas c1("c1_print_temp", "temp printer");
  c1.SetLogy();
  Double_t x1 = 0.6, x2 = x1+0.35, y1 = 0.7, y2 = y1+0.2;
  for (unsigned int i = 0; i < 63; i++)
    {
      TH1F* dd_qcd = GetDataDrivenHist("qcdFromCRs", sr_key[i]);    
      TH1F* mc_qcd = GetMonteCarloHist("qcd_ht", sr_key[i]);
      mc_qcd->SetLineColor(kRed);
      TLegend * tl_qcd = new TLegend(x1, y1, x2, y2);
      tl_qcd->AddEntry(dd_qcd);
      tl_qcd->AddEntry(mc_qcd);
      
      TH1F* dd_ll = GetDataDrivenHist("lostlepFromCRs", sr_key[i]);
      TH1F* mc_ll = GetMonteCarloHist("lostlepton", sr_key[i]);
      mc_ll->SetLineColor(kRed);
      TLegend * tl_ll = new TLegend(x1, y1, x2, y2);
      tl_ll->AddEntry(dd_ll);
      tl_ll->AddEntry(mc_ll);
      
      // need this workaround because 3UH does not exist for zinvFromDY
      TH1F* dd_zdy;
      if (i != 42)
	{
	  dd_zdy = GetDataDrivenHist("zinvFromDY", sr_key[i]);
	}
      // need this workaround because 11L and the super signal regions 20+
      // do not exist for zinvFromGJ 
      TH1F* dd_zgj; 
      if (i != 17 && i < 50) 
	{
	  dd_zgj = GetDataDrivenHist("zinvFromGJ", sr_key[i]);
	  dd_zgj->SetLineColor(kGreen);
	}
      TH1F* mc_z = GetMonteCarloHist("zinv_ht", sr_key[i]);

      mc_z->SetLineColor(kRed);
      TLegend * tl_z = new TLegend(x1, y1, x2, y2);
      if (i != 42) tl_z->AddEntry(dd_zdy);
      if (i != 17 && i < 50) tl_z->AddEntry(dd_zgj);
      tl_z->AddEntry(mc_z);

      double MaxToSet, MinToSet;
      
      MaxToSet = max(mc_qcd->GetMaximum(), dd_qcd->GetMaximum());
      MinToSet = min(mc_qcd->GetMinimum(), dd_qcd->GetMinimum());
      mc_qcd->SetMaximum( 10 * MaxToSet );
      mc_qcd->SetMinimum( MinToSet > 0 ? MinToSet / 10 : 0.0001);
      mc_qcd->SetTitle("QCD M_{T2} Distributions;M_{T2} (GeV);Count @ 35.9 fb^{-1}");
      mc_qcd->Draw("E1E0");
      dd_qcd->Draw("E1E0 same");
      tl_qcd->Draw();
      c1.SaveAs( ("PDFs/qcd_estimates_"+sr_key[i]+".pdf").c_str() );

      MaxToSet = max(mc_ll->GetMaximum(), dd_ll->GetMaximum());
      MinToSet = min(mc_ll->GetMinimum(), dd_ll->GetMinimum());
      mc_ll->SetMaximum( 10 * MaxToSet ); 
      mc_ll->SetMinimum( MinToSet > 0 ? MinToSet / 10 : 0.0001);
      mc_ll->SetTitle("Lost Lepton M_{T2} Distributions;M_{T2} (GeV);Count @ 35.9 fb^{-1}");
      mc_ll->Draw("E1E0");
      dd_ll->Draw("E1E0 same");
      tl_ll->Draw();
      c1.SaveAs( ("PDFs/lostlep_estimates_"+sr_key[i]+".pdf").c_str() );
      
      double zdy_max = 0.0, zgj_max = 0.0, zdy_min = FLT_MAX, zgj_min = FLT_MAX;
      if (i != 42) zdy_max = dd_zdy->GetMaximum();
      if (i != 17 && i < 50) zgj_max = dd_zgj->GetMaximum();
      MaxToSet = max( mc_z->GetMaximum(), max(zdy_max, zgj_max));
      MinToSet = min( mc_z->GetMinimum(), min(zdy_min, zgj_min));
      mc_z->SetMaximum( 10 * MaxToSet );
      mc_z->SetMinimum( MinToSet > 0 ? MinToSet / 10 : 0.0001);
      mc_z->SetTitle("Z->#nu#nu M_{T2} Distributions;M_{T2} (GeV);Count @ 35.9 fb^{-1}");
      mc_z->Draw("E1E0");
      // see comments above
      if (i != 42) dd_zdy->Draw("E1E0 same");
      if (i != 17 && i < 50) dd_zgj->Draw("E1E0 same");
      tl_z->Draw();
      c1.SaveAs( ("PDFs/zinv_estimates_"+sr_key[i]+".pdf").c_str() );

      // ratio plots


    }
  
}
