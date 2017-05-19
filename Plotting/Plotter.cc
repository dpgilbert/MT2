// C++
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include <stdexcept>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"

//#include "RooRealVar.h"
//#include "RooDataSet.h"

// Tools
#include "../../CORE/Tools/utils.h"

#include "Plotting.h"

using namespace std;

int main ()
{
  vector<string> file_list;
  file_list.push_back("ww");
  file_list.push_back("twz");
  file_list.push_back("tttt");
  file_list.push_back("tth");
  file_list.push_back("ttw");
  file_list.push_back("ttz");
  file_list.push_back("singletop");
  file_list.push_back("ttdl");
  file_list.push_back("ttsl");
  file_list.push_back("ttg");
  file_list.push_back("zinv");
  file_list.push_back("dyjets");
  file_list.push_back("wjets");
  file_list.push_back("qcd"); 

  // Legend location parameters
  Double_t x1 = 0.8, x2 = x1+0.2, y1 = 0.5, y2 = y1+0.4;
  // Turn off stat box
  gStyle->SetOptStat(0);
  // Use a single canvas for all prints
  TCanvas c1("c1_print_temp", "temp printer");
  c1.cd();

  map< string, TH1F* > hist_list_1D;

  for (vector<string>::iterator it = file_list.begin(); it != file_list.end(); ++it)
    {
      string file_name = *it;
      
      cout << "loading sample: " << file_name << endl;
      
      TFile * current_file = TFile::Open( ("../output/Unskimmed/"+file_name+".root").c_str() );

      int kColor = kBlack;
      
      if      (file_name.find("qcd") != string::npos)  kColor = kRed;

      else if (file_name.find("ttg") != string::npos)  kColor = kOrange;

      else if (file_name.find("ttsl") != string::npos) kColor = kSpring;
      else if (file_name.find("ttdl") != string::npos) kColor = kSpring-7;

      else if (file_name.find("ttz") != string::npos)  kColor = kCyan;
      else if (file_name.find("ttw") != string::npos)  kColor = kCyan+2;
      else if (file_name.find("tth") != string::npos)  kColor = kCyan+4;

      else if (file_name.find("tttt") != string::npos) kColor = kCyan-10;

      else if (file_name.find("singletop") != string::npos) kColor = kYellow;
      else if (file_name.find("twz") != string::npos)       kColor = kYellow-6;
      
      else if (file_name.find("ww") != string::npos)    kColor = kBlue;
      else if (file_name.find("wjets") != string::npos) kColor = kBlue-7;

      else if (file_name.find("dyjets") != string::npos) kColor = kMagenta;
      else if (file_name.find("zinv") != string::npos)   kColor = kMagenta-7;
      else cout << "unexpected file name: " << file_name << endl;

      for (TObjLink* link = gDirectory->GetListOfKeys()->FirstLink(); link != NULL; link = link->Next())
	{ 
	  string name = link->GetObject()->GetName();
	  if  (name.find("htmet") != string::npos 
	       || name.find("diffdom") != string::npos
	       || name.find("njmt2") != string::npos
	       || name.find("njbj") != string::npos)
	    
	    {
	      if ( TH2F* h2 = dynamic_cast<TH2F*>(gDirectory->Get(name.c_str()) ) )
		{
		  // just print 2D histograms without stacking
		  h2->Draw("colz");
		  c1.Print( ("PDFs/"+file_name+"_"+name+".pdf").c_str() );
		}
	      else cout << "name matched TH2F but cast failed" << endl;
	    }
	  else if (TH1F* h1 = dynamic_cast<TH1F*>(gDirectory->Get(name.c_str())))
	    {
	      TH1F* hist_1d = new TH1F(*h1);
	      hist_1d->SetDirectory(0);
	      hist_1d->SetFillColor(kColor);
	      hist_1d->SetLineColor(kColor);
	      hist_list_1D[file_name+"_"+name] = hist_1d;
	    }
	  else
	    {
	      cout << "Failed to ID TObject with name: " << name << " in sample " << file_name << endl;
	    }
	    
	}
      current_file->Close();
    }

  /*
    Add in the order:
    ww
    twz
    tttt
    tth
    ttw
    ttz
    singletop    
    ttdl
    ttsl
    ttg    
    zinv   
    dyjets
    wjets
    QCD
*/


  /*
    STACKS
   */

  THStack *hs_mt2_nocut = new THStack("hs_mt2_nocut", "Stacked Initial M_{T2}");
  THStack *hs_mt2_trigger = new THStack("hs_mt2_trigger", "Stacked Post-Trigger M_{T2}");
  THStack *hs_mt2_nm1 = new THStack("hs_mt2_nm1", "Stacked M_{T2}, All Other Cuts");

  THStack *hs_ht_nocut = new THStack("hs_ht_nocut", "Stacked Initial H_{T}");
  THStack *hs_ht_trigger = new THStack("hs_ht_trigger", "Stacked Post-Trigger H_{T}"); 

  THStack *hs_dphi_nocut = new THStack("hs_dphi_nocut", "Stacked Initial #Delta#phi_{min} Distribution");
  THStack *hs_dphi_trigger = new THStack("hs_dphi_trigger", "Stacked Post-Trigger #Delta#phi_{min} Distribution");
  THStack *hs_dphi_nm1 = new THStack("hs_dphi_nm1", "Stacked #Delta#phi_{min} Distribution, All Other Cuts Applied");

  THStack *hs_diff_nocut = new THStack("hs_diff_nocut", "Stacked Initial |MHT-MET| Distribution");
  THStack *hs_diff_trigger = new THStack("hs_diff_trigger", "Stacked Post-Trigger |MHT-MET| Distribution");
  THStack *hs_diff_nm1 = new THStack("hs_diff_nm1", "Stacked |MHT-MET| Distribution, All Other Cuts Applied");

  THStack *hs_dom_nocut = new THStack("hs_dom_nocut", "Stacked Initial |MHT-MET|/MET Distribution");
  THStack *hs_dom_trigger = new THStack("hs_dom_trigger", "Stacked Post-Trigger |MHT-MET|/MET Distribution");
  THStack *hs_dom_nm1 = new THStack("hs_dom_nm1", "Stacked |MHT-MET|/MET Distribution, All Other Cuts Applied");

  THStack *hs_njet_nocut = new THStack("hs_njet_nocut", "Stacked Initial N_{J} Distribution");
  THStack *hs_njet_trigger = new THStack("hs_njet_trigger", "Stacked Post-Trigger N_{J} Distribution");
  THStack *hs_njet_nm1 = new THStack("hs_njet_nm1", "Stacked N_{J} Distribution, All Other Cuts Applied");

  THStack *hs_bjet_nocut = new THStack("hs_bjet_nocut", "Stacked Initial B-tag Multiplicity Distribution");
  THStack *hs_bjet_trigger = new THStack("hs_bjet_nm1", "Stacked B-tag Multiplicity Distribution, All Other Cuts Applied");

  THStack *hs_nlep_nocut = new THStack("hs_nlep_nocut", "Stacked Initial Lepton Veto Index Distribution");
  THStack *hs_nlep_trigger = new THStack("hs_nlep_trigger", "Stacked Post-Trigger Lepton Veto Index Distribution");
  THStack *hs_nlep_nm1 = new THStack("hs_nlep_nm1", "Stacked Lepton Veto Index Distribution, All Other Cuts Applied");

  THStack *hs_nll_nocut = new THStack("hs_nll_nocut", "Stacked Initial Light Lepton Distribution");
  THStack *hs_nll_trigger = new THStack("hs_nll_trigger", "Stacked Post-Trigger Light Lepton Distribution");
  THStack *hs_nll_nm1 = new THStack("hs_nll_nm1", "Stacked Light Lepton Distribution, All Other Cuts Applied");

  THStack *hs_lowmt_nocut = new THStack("hs_lowmt_nocut", "Stacked Initial nPFLep5LowMT Distribution");
  THStack *hs_lowmt_trigger = new THStack("hs_lowmt_trigger", "Stacked Post-Trigger nPFLep5LowMT Distribution");
  THStack *hs_lowmt_nm1 = new THStack("hs_lowmt_nm1", "Stacked nPFLep5LowMT Distribution, All Other Cuts Applied");

  // Set c1 y axis to log for printing 1D histograms
  c1.SetLogy();

  // Legends
  TLegend *mt2_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *mt2_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *mt2_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *ht_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *ht_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *dphi_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *dphi_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *dphi_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *diff_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *diff_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *diff_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *dom_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *dom_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *dom_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *njet_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *njet_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *njet_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *bjet_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *bjet_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *nlep_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *nlep_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *nlep_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *nll_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *nll_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *nll_trig_leg = new TLegend(x1, y1, x2, y2);
  TLegend *lowmt_nc_leg = new TLegend(x1, y1, x2, y2);
  TLegend *lowmt_nm1_leg = new TLegend(x1, y1, x2, y2);
  TLegend *lowmt_trig_leg = new TLegend(x1, y1, x2, y2);

  TH1F* temp; 
  for (vector<string>::iterator it = file_list.begin(); it != file_list.end(); ++it)
    {
      const string sample = (*it);

      cout << "stacking sample: " << sample << endl;

      // mt2 stack  
      temp = hist_list_1D.at( sample  + "_h_mt2_nocut");
      hs_mt2_nocut->Add(temp, "hist");
      mt2_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_mt2_trigger");
      hs_mt2_trigger->Add(temp, "hist");
      mt2_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_mt2_nm1");
      hs_mt2_nm1->Add(temp, "hist");
      mt2_nm1_leg->AddEntry(temp, sample.c_str());

      // ht stack (no nm1)
      temp = hist_list_1D.at( sample  + "_h_ht_nocut");
      hs_ht_nocut->Add(temp, "hist");
      ht_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_ht_trigger");
      hs_ht_trigger->Add(temp, "hist");
      ht_trig_leg->AddEntry(temp, sample.c_str());

      // dphi
      temp = hist_list_1D.at( sample  + "_h_dphi_nocut");
      hs_dphi_nocut->Add(temp, "hist");
      dphi_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_dphi_trigger");
      hs_dphi_trigger->Add(temp, "hist");
      dphi_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_dphi_nm1");
      hs_dphi_nm1->Add(temp, "hist");
      dphi_nm1_leg->AddEntry(temp, sample.c_str());

      // diff
      temp = hist_list_1D.at( sample  + "_h_diff_nocut");
      hs_diff_nocut->Add(temp, "hist");
      diff_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_diff_trigger");
      hs_diff_trigger->Add(temp, "hist");
      diff_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_diff_nm1");
      hs_diff_nm1->Add(temp, "hist");
      diff_nm1_leg->AddEntry(temp, sample.c_str());

      // dom
      temp = hist_list_1D.at( sample  + "_h_dom_nocut");
      hs_dom_nocut->Add(temp, "hist");
      dom_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_dom_trigger");
      hs_dom_trigger->Add(temp, "hist");
      dom_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_dom_nm1");
      hs_dom_nm1->Add(temp, "hist");
      dom_nm1_leg->AddEntry(temp, sample.c_str());

      // njet
      temp = hist_list_1D.at( sample  + "_h_njet_nocut");
      hs_njet_nocut->Add(temp, "hist");
      njet_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_njet_trigger");
      hs_njet_trigger->Add(temp, "hist");
      njet_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_njet_nm1");
      hs_njet_nm1->Add(temp, "hist");
      njet_nm1_leg->AddEntry(temp, sample.c_str());
      

      // bjet
      temp = hist_list_1D.at( sample  + "_h_bjet_nocut");
      hs_bjet_nocut->Add(temp, "hist");
      bjet_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_bjet_trigger");
      hs_bjet_trigger->Add(temp, "hist");
      bjet_trig_leg->AddEntry(temp, sample.c_str());

      // nlep
      temp = hist_list_1D.at( sample  + "_h_nlep_nocut");
      hs_nlep_nocut->Add(temp, "hist");
      nlep_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_nlep_trigger");
      hs_nlep_trigger->Add(temp, "hist");
      nlep_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_nlep_nm1");
      hs_nlep_nm1->Add(temp, "hist");
      nlep_nm1_leg->AddEntry(temp, sample.c_str());

      // nll
      temp = hist_list_1D.at( sample  + "_h_nll_nocut");
      hs_nll_nocut->Add(temp, "hist");
      nll_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_nll_trigger");
      hs_nll_trigger->Add(temp, "hist");
      nll_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_nll_nm1");
      hs_nll_nm1->Add(temp, "hist");
      nll_nm1_leg->AddEntry(temp, sample.c_str());

      // lowmt
      temp = hist_list_1D.at( sample  + "_h_lowmt_nocut");
      hs_lowmt_nocut->Add(temp, "hist");
      lowmt_nc_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_lowmt_trigger");
      hs_lowmt_trigger->Add(temp, "hist");
      lowmt_trig_leg->AddEntry(temp, sample.c_str());

      temp = hist_list_1D.at( sample + "_h_lowmt_nm1");
      hs_lowmt_nm1->Add(temp, "hist");
      lowmt_nm1_leg->AddEntry(temp, sample.c_str());

    }

  hs_mt2_nocut->Draw();
  mt2_nc_leg->Draw();
  CopyAxes(hs_mt2_nocut, hist_list_1D.at("zinv_h_mt2_nocut"), c1);
  c1.Print("PDFs/hs_mt2_nocut.pdf");
  hs_mt2_trigger->Draw();
  mt2_trig_leg->Draw();
  CopyAxes(hs_mt2_trigger, hist_list_1D.at("zinv_h_mt2_trigger"), c1);
  c1.Print("PDFs/hs_mt2_trigger.pdf");
  hs_mt2_nm1->Draw();
  mt2_nm1_leg->Draw();
  CopyAxes(hs_mt2_nm1, hist_list_1D.at("zinv_h_mt2_nm1"), c1);
  c1.Print("PDFs/hs_mt2_nm1.pdf");

  hs_ht_nocut->Draw();
  ht_nc_leg->Draw();
  CopyAxes(hs_ht_nocut, hist_list_1D.at("zinv_h_ht_nocut"), c1);
  c1.Print("PDFs/hs_ht_nocut.pdf");
  hs_ht_trigger->Draw();
  ht_trig_leg->Draw();
  CopyAxes(hs_ht_trigger, hist_list_1D.at("zinv_h_ht_trigger"), c1);
  c1.Print("PDFs/hs_ht_trigger.pdf");

  hs_dphi_nocut->Draw();
  dphi_nc_leg->Draw();
  CopyAxes(hs_dphi_nocut, hist_list_1D.at("zinv_h_dphi_nocut"), c1);
  c1.Print("PDFs/hs_dphi_nocut.pdf");
  hs_dphi_trigger->Draw();
  dphi_trig_leg->Draw();
  CopyAxes(hs_dphi_trigger, hist_list_1D.at("zinv_h_dphi_trigger"), c1);
  c1.Print("PDFs/hs_dphi_trigger.pdf");
  hs_dphi_nm1->Draw();
  dphi_nm1_leg->Draw();
  CopyAxes(hs_dphi_nm1, hist_list_1D.at("zinv_h_dphi_nm1"), c1);
  c1.Print("PDFs/hs_dphi_nm1.pdf");

  hs_diff_nocut->Draw();
  diff_nc_leg->Draw();
  CopyAxes(hs_diff_nocut, hist_list_1D.at("zinv_h_diff_nocut"), c1);
  c1.Print("PDFs/hs_diff_nocut.pdf");
  hs_diff_trigger->Draw();
  diff_trig_leg->Draw();
  CopyAxes(hs_diff_trigger, hist_list_1D.at("zinv_h_diff_trigger"), c1);
  c1.Print("PDFs/hs_diff_trigger.pdf");
  hs_diff_nm1->Draw();
  diff_nm1_leg->Draw();
  CopyAxes(hs_diff_nm1, hist_list_1D.at("zinv_h_diff_nm1"), c1);
  c1.Print("PDFs/hs_diff_nm1.pdf");

  hs_dom_nocut->Draw();
  dom_nc_leg->Draw();
  CopyAxes(hs_dom_nocut, hist_list_1D.at("zinv_h_dom_nocut"), c1);
  c1.Print("PDFs/hs_dom_nocut.pdf");
  hs_dom_trigger->Draw();
  dom_trig_leg->Draw();
  CopyAxes(hs_dom_trigger, hist_list_1D.at("zinv_h_dom_trigger"), c1);
  c1.Print("PDFs/hs_dom_trigger.pdf");
  hs_dom_nm1->Draw();
  dom_nm1_leg->Draw();
  CopyAxes(hs_dom_nm1, hist_list_1D.at("zinv_h_dom_nm1"), c1);
  c1.Print("PDFs/hs_dom_nm1.pdf");

  hs_njet_nocut->Draw();
  njet_nc_leg->Draw();
  CopyAxes(hs_njet_nocut, hist_list_1D.at("zinv_h_njet_nocut"), c1);
  c1.Print("PDFs/hs_njet_nocut.pdf");
  hs_njet_trigger->Draw();
  njet_trig_leg->Draw();
  CopyAxes(hs_njet_trigger, hist_list_1D.at("zinv_h_njet_trigger"), c1);
  c1.Print("PDFs/hs_njet_trigger.pdf");
  hs_njet_nm1->Draw();
  njet_nm1_leg->Draw();
  CopyAxes(hs_njet_nm1, hist_list_1D.at("zinv_h_njet_nm1"), c1);
  c1.Print("PDFs/hs_njet_nm1.pdf");

  hs_bjet_nocut->Draw();
  bjet_nc_leg->Draw();
  CopyAxes(hs_bjet_nocut, hist_list_1D.at("zinv_h_bjet_nocut"), c1);
  c1.Print("PDFs/hs_bjet_nocut.pdf");
  hs_bjet_trigger->Draw();
  bjet_trig_leg->Draw();
  CopyAxes(hs_bjet_trigger, hist_list_1D.at("zinv_h_bjet_trigger"), c1);
  c1.Print("PDFs/hs_bjet_trigger.pdf");

  hs_nlep_nocut->Draw();
  nlep_nc_leg->Draw();
  CopyAxes(hs_nlep_nocut, hist_list_1D.at("zinv_h_nlep_nocut"), c1);
  c1.Print("PDFs/hs_nlep_nocut.pdf");
  hs_nlep_trigger->Draw();
  nlep_trig_leg->Draw();
  CopyAxes(hs_nlep_trigger, hist_list_1D.at("zinv_h_nlep_trigger"), c1);
  c1.Print("PDFs/hs_nlep_trigger.pdf");
  hs_nlep_nm1->Draw();
  nlep_nm1_leg->Draw();
  CopyAxes(hs_nlep_nm1, hist_list_1D.at("zinv_h_nlep_nm1"), c1);
  c1.Print("PDFs/hs_nlep_nm1.pdf");

  hs_nll_nocut->Draw();
  nll_nc_leg->Draw();
  CopyAxes(hs_nll_nocut, hist_list_1D.at("zinv_h_nll_nocut"), c1);
  c1.Print("PDFs/hs_nll_nocut.pdf");
  hs_nll_trigger->Draw();
  nll_trig_leg->Draw();
  CopyAxes(hs_nll_trigger, hist_list_1D.at("zinv_h_nll_trigger"), c1);
  c1.Print("PDFs/hs_nll_trigger.pdf");
  hs_nll_nm1->Draw();
  nll_nm1_leg->Draw();
  CopyAxes(hs_nll_nm1, hist_list_1D.at("zinv_h_nll_nm1"), c1);
  c1.Print("PDFs/hs_nll_nm1.pdf");

  hs_lowmt_nocut->Draw();
  lowmt_nc_leg->Draw();
  CopyAxes(hs_lowmt_nocut, hist_list_1D.at("zinv_h_lowmt_nocut"), c1);
  c1.Print("PDFs/hs_lowmt_nocut.pdf");
  hs_lowmt_trigger->Draw();
  lowmt_trig_leg->Draw();
  CopyAxes(hs_lowmt_trigger, hist_list_1D.at("zinv_h_lowmt_trigger"), c1);
  c1.Print("PDFs/hs_lowmt_trigger.pdf");
  hs_lowmt_nm1->Draw();
  lowmt_nm1_leg->Draw();
  CopyAxes(hs_lowmt_nm1, hist_list_1D.at("zinv_h_lowmt_nm1"), c1);
  c1.Print("PDFs/hs_lowmt_nm1.pdf");

}

void CopyAxes (THStack * hs, TH1* h, TCanvas& c)
{
  hs->GetXaxis()->SetTitle(h->GetXaxis()->GetTitle());
  hs->GetYaxis()->SetTitle(h->GetYaxis()->GetTitle());
  c.Modified();
} 
