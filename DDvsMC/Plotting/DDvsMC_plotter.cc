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
  tf->Close();
  return toReturn;
}

TH1F* GetMonteCarloHist (const string& filename, const string& SR_key)
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
			

  // turn off stat box
  gStyle->SetOptStat(0);
  TCanvas c1("c1_print_temp", "temp printer");
  c1.SetLogy();
  Double_t x1 = 0.8, x2 = x1+0.2, y1 = 0.5, y2 = y1+0.4;
  for (unsigned int i = 0; i < 63; i++)
    {
      TH1F* dd_qcd = GetDataDrivenHist("qcdFromCRs", sr_key[i]);    
      TH1F* mc_qcd = GetMonteCarloHist("qcd_ht", sr_key[i]);
      mc_qcd->SetLineColor(kRed);
      TLegend * tl_qcd = new TLegend(x1, x2, y1, y2);
      tl_qcd->AddEntry(dd_qcd);
      tl_qcd->AddEntry(mc_qcd);
      
      TH1F* dd_ll = GetDataDrivenHist("lostlepFromCRs", sr_key[i]);
      TH1F* mc_ll = GetMonteCarloHist("lostlepton", sr_key[i]);
      mc_ll->SetLineColor(kRed);
      TLegend * tl_ll = new TLegend(x1, x2, y1, y2);
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
      TLegend * tl_z = new TLegend(x1, x2, y1, y2);
      if (i != 42) tl_z->AddEntry(dd_zdy);
      if (i != 17) tl_z->AddEntry(dd_zgj);
      tl_z->AddEntry(mc_z);

      mc_qcd->Draw();
      dd_qcd->Draw("same");
      tl_qcd->Draw();
      c1.SaveAs( ("PDFs/qcd_estimates_"+sr_key[i]+".pdf").c_str() );

      mc_ll->Draw();
      dd_ll->Draw("same");
      tl_ll->Draw();
      c1.SaveAs( ("PDFs/lostlep_estimates_"+sr_key[i]+".pdf").c_str() );
      
      mc_z->Draw();
      // see comments above
      if (i != 42) dd_zdy->Draw("same");
      if (i != 17 && i < 50) dd_zgj->Draw("same");
      tl_z->Draw();
      c1.SaveAs( ("PDFs/zinv_estimates_"+sr_key[i]+".pdf").c_str() );
    }
  
}
