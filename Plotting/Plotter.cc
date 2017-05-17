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

//#include "RooRealVar.h"
//#include "RooDataSet.h"

// Tools
#include "../../CORE/Tools/utils.h"

using namespace std;

int main ()
{
  vector<string> file_list;
  file_list.push_back("qcd"); 
  file_list.push_back("ttg");
  file_list.push_back("ttsl");
  file_list.push_back("ttdl");
  file_list.push_back("ttz");
  file_list.push_back("ttw");
  file_list.push_back("tth");
  file_list.push_back("tttt");
  file_list.push_back("singletop");
  file_list.push_back("twz");
  file_list.push_back("ww");
  file_list.push_back("wjets");
  file_list.push_back("dyjets");
  file_list.push_back("zinv");

  TCanvas c1("c1_print_temp", "temp printer");
  c1.SetLogy();
  c1.cd();

  map< string, TH1F* > hist_list_1D;
  map< string, TH2F* > hist_list_2D;

  for (vector<string>::iterator it = file_list.begin(); it != file_list.end(); ++it)
    {
      string file_name = *it;
      
      cout << file_name << endl;
      
      TFile * current_file = TFile::Open( ("../output/Unskimmed/"+file_name+".root").c_str() );

      int kColor = kBlack;
      
      if      (file_name.find("qcd") != string::npos)  kColor = kRed;

      else if (file_name.find("ttg") != string::npos)  kColor = kSpring;
      else if (file_name.find("ttsl") != string::npos) kColor = kSpring-1;
      else if (file_name.find("ttdl") != string::npos) kColor = kSpring-3;
      else if (file_name.find("ttz") != string::npos)  kColor = kSpring-5;
      else if (file_name.find("ttw") != string::npos)  kColor = kSpring-7;
      else if (file_name.find("tth") != string::npos)  kColor = kSpring-9;

      else if (file_name.find("tttt") != string::npos) kColor = kSpring+10;

      else if (file_name.find("singletop") != string::npos) kColor = kYellow;
      else if (file_name.find("twz") != string::npos)       kColor = kYellow-7;
      
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
		  TH2F* hist_2d = new TH2F(*h2);
		  hist_2d->SetDirectory(0);
		  hist_2d->SetFillColor(kColor);
		  hist_list_2D[file_name+"_"+name] = hist_2d;
		}
	      else cout << "name matched TH2F but cast failed" << endl;
	    }
	  else if (TH1F* h1 = dynamic_cast<TH1F*>(gDirectory->Get(name.c_str())))
	    {
	      TH1F* hist_1d = new TH1F(*h1);
	      hist_1d->SetDirectory(0);
	      hist_1d->SetFillColor(kColor);
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
    QCD
    ttg
    ttsl
    ttdl
    ttz
    ttw
    tth
    tttt
    singletop
    twz
    ww
    wjets
    dyjets
    zinv
   */


  THStack *hs_mt2_nocut = new THStack("hs_mt2_nocut", "Stacked Initial M_{T2}");
  THStack *hs_mt2_trigger = new THStack("hs_mt2_trigger", "Stacked Post-Trigger M_{T2}");
  THStack *hs_mt2_nm1 = new THStack("hs_mt2_nm1", "Stacked M_{T2}, All Other Cuts");

  THStack *hs_ht_nocut = new THStack("hs_ht_nocut", "Stacked Initial H_{T}");
  THStack *hs_ht_trigger = new THStack("hs_ht_trigger", "Stacked Post-Trigger H_{T}"); 
  THStack *hs_ht_nm1 = new THStack("hs_ht_nm1", "Stacked H_{T}, All Other Cuts");


  Double_t x1 = 0.6, x2 = x1+0.25, y1 = 0.7, y2 = y1+0.2;
  TLegend *mt2_nc_leg = new TLegend(x1, x2, y1, y2);
  TLegend *mt2_nm1_leg = new TLegend(x1, x2, y1, y2);
  TLegend *mt2_trig_leg = new TLegend(x1, x2, y1, y2);
  TLegend *ht_nc_leg = new TLegend(x1, x2, y1, y2);
  TLegend *ht_nm1_leg = new TLegend(x1, x2, y1, y2);
  TLegend *ht_trig_leg = new TLegend(x1, x2, y1, y2);

  // mt2 stack  
  TH1F* temp; 
  for (vector<string>::iterator it = file_list.begin(); it != file_list.end(); ++it)
    {
      temp = hist_list_1D.at( (*it) + "_h_mt2_nocut");
      hs_mt2_nocut->Add(temp);
      mt2_nc_leg->AddEntry(temp);

      temp = hist_list_1D.at( (*it) + "_h_mt2_trigger");
      hs_mt2_trigger->Add(temp);
      mt2_trig_leg->AddEntry(temp);

      temp = hist_list_1D.at( (*it) + "_h_mt2_nm1");
      hs_mt2_nm1->Add(temp);
      mt2_nm1_leg->AddEntry(temp);

    }

  hs_mt2_nocut->Draw();
  mt2_nc_leg->Draw();
  c1.Print("hs_mt2_nocut.pdf");
  hs_mt2_trigger->Draw();
  mt2_trig_leg->Draw();
  c1.Print("hs_mt2_trigger.pdf");
  hs_mt2_nm1->Draw();
  mt2_nm1_leg->Draw();
  c1.Print("hs_mt2_nm1.pdf");
}

