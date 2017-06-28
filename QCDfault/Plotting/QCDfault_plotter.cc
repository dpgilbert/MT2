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
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"
#include "TString.h"

#include "QCDfault_plotter.h"

using namespace std;

int main ()
{
  vector<string> file_list;
  file_list.push_back("hists300to500");
  file_list.push_back("hists500to700");
  file_list.push_back("hists700to1000");
  file_list.push_back("hists1000to1500");
  file_list.push_back("hists1500to2000");
  file_list.push_back("hists2000toInf");

  // Legend location parameters
  Double_t x1 = 0.8, x2 = x1+0.2, y1 = 0.5, y2 = y1+0.4;
  // Turn off stat box
  gStyle->SetOptStat(0);
  // Use a single canvas for all prints
  TCanvas c1("c1_print_temp", "temp printer");

  for (vector<string>::iterator it = file_list.begin(); it != file_list.end(); ++it)
    {
      string file_name = *it;
      
      cout << "loading sample: " << file_name << endl;
      
      TFile * current_file = TFile::Open( ("../output/"+file_name+".root").c_str() );

      int kColor = kBlack;
      float scale = 0.0;

      if      (file_name.find("300to500") != string::npos)  {kColor = kRed; scale = 7.1915731; }
      else if (file_name.find("500to700") != string::npos)  {kColor = kOrange; scale = 0.5380254; }
      else if (file_name.find("700to1000") != string::npos) {kColor = kMagenta; scale = 0.1572858; }
      else if (file_name.find("1000to1500") != string::npos)  {kColor = kCyan; scale = 0.0839777; }
      else if (file_name.find("1500to2000") != string::npos) {kColor = kBlue; scale = 0.0107290; }
      else if (file_name.find("2000toInf") != string::npos) {kColor = kGreen; scale = 0.0048347; }
      else {cout << "Impossible file name " << file_name << ", aborting...." << endl;}

      for (TObjLink* link = gDirectory->GetListOfKeys()->FirstLink(); link != NULL; link = link->Next())
	{ 
	  string name = link->GetObject()->GetName();
	  if (TH1F* h1 = dynamic_cast<TH1F*>(gDirectory->Get(name.c_str())))
	    {
	      TH1F* hist_1d = new TH1F(*h1);
	      hist_1d->SetDirectory(0);
	      hist_1d->Scale( 1 / scale );
	      hist_1d->Draw("hist");
	      hist_1d->SetTitle( (file_name+" "+name+" Raw Counts;M_{T2} (GeV);MC Events in Bin").c_str() );
	      c1.SaveAs( ("PNGs/Raw/"+file_name+"_"+name+".png").c_str());
	      hist_1d->SetFillColor(kColor);
	      hist_1d->SetLineColor(kColor);
	      hist_1d->Scale(35.9*scale);
	      hist_1d->SetTitle( (file_name+" "+name+" M_{T2} Distribution;M_{T2} (GeV);Counts @ 35.9 fb^{-1}").c_str());
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
    STACKS
   */

  THStack *hs_1VL = new THStack("hs_1VL", "1VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_2VL = new THStack("hs_2VL", "2VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_3VL = new THStack("hs_3VL", "3VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_12VL = new THStack("hs_12VL", "12VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_13VL = new THStack("hs_13VL", "13VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_14VL = new THStack("hs_14VL", "14VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_15VL = new THStack("hs_15VL", "15VL QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");

  THStack *hs_1L = new THStack("hs_1L", "1L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_2L = new THStack("hs_2L", "2L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_3L = new THStack("hs_3L", "3L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_4L = new THStack("hs_4L", "4L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_5L = new THStack("hs_5L", "5L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_6L = new THStack("hs_6L", "6L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_7L = new THStack("hs_7L", "7L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_8L = new THStack("hs_8L", "8L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_9L = new THStack("hs_9L", "9L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_10L = new THStack("hs_10L", "10L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_11L = new THStack("hs_11L", "11L QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");

  THStack *hs_1M = new THStack("hs_1M", "1M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_2M = new THStack("hs_2M", "2M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_3M = new THStack("hs_3M", "3M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_4M = new THStack("hs_4M", "4M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_5M = new THStack("hs_5M", "5M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_6M = new THStack("hs_6M", "6M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_7M = new THStack("hs_7M", "7M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_8M = new THStack("hs_8M", "8M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_9M = new THStack("hs_9M", "9M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_10M = new THStack("hs_10M", "10M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_11M = new THStack("hs_11M", "11M QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");

  THStack *hs_1H = new THStack("hs_1H", "1H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_2H = new THStack("hs_2H", "2H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_3H = new THStack("hs_3H", "3H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_4H = new THStack("hs_4H", "4H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_5H = new THStack("hs_5H", "5H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_6H = new THStack("hs_6H", "6H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_7H = new THStack("hs_7H", "7H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_8H = new THStack("hs_8H", "8H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_9H = new THStack("hs_9H", "9H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_10H = new THStack("hs_10H", "10H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_11H = new THStack("hs_11H", "11H QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");

  THStack *hs_1UH = new THStack("hs_1UH", "1UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_2UH = new THStack("hs_2UH", "2UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_3UH = new THStack("hs_3UH", "3UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_4UH = new THStack("hs_4UH", "4UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_5UH = new THStack("hs_5UH", "5UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_6UH = new THStack("hs_6UH", "6UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_7UH = new THStack("hs_7UH", "7UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_8UH = new THStack("hs_8UH", "8UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_9UH = new THStack("hs_9UH", "9UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_10UH = new THStack("hs_10UH", "10UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");
  THStack *hs_11UH = new THStack("hs_11UH", "11UH QCD, Distinguished by Gen H_{T};M_{T2} (GeV);Counts at 35.9 fb^{-1}");

  // Set c1 y axis to log
  c1.SetLogy();

  // Legends
  TLegend *sr1VL_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr2VL_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr3VL_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr12VL_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr13VL_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr14VL_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr15VL_leg = new TLegend(x1, y1, x2, y2);

  TLegend *sr1L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr2L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr3L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr4L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr5L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr6L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr7L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr8L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr9L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr10L_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr11L_leg = new TLegend(x1, y1, x2, y2);

  TLegend *sr1M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr2M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr3M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr4M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr5M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr6M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr7M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr8M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr9M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr10M_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr11M_leg = new TLegend(x1, y1, x2, y2);

  TLegend *sr1H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr2H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr3H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr4H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr5H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr6H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr7H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr8H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr9H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr10H_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr11H_leg = new TLegend(x1, y1, x2, y2);

  TLegend *sr1UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr2UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr3UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr4UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr5UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr6UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr7UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr8UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr9UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr10UH_leg = new TLegend(x1, y1, x2, y2);
  TLegend *sr11UH_leg = new TLegend(x1, y1, x2, y2);



  TH1F* temp; 
  for (vector<string>::iterator it = file_list.begin(); it != file_list.end(); ++it)
    {
      const string sample = (*it);

      cout << "stacking sample: " << sample << endl;

      // sr 1VL stack
      temp = hist_list_1D.at( sample  + "_1VL");
      hs_1VL->Add(temp, "hist");
      sr1VL_leg->AddEntry(temp, sample.c_str());

      // sr 2VL 
      temp = hist_list_1D.at( sample + "_2VL");
      hs_2VL->Add(temp, "hist");
      sr2VL_leg->AddEntry(temp, sample.c_str());

      // sr 3VL 
      temp = hist_list_1D.at( sample + "_3VL");
      hs_3VL->Add(temp, "hist");
      sr3VL_leg->AddEntry(temp, sample.c_str());

      // 12VL
      temp = hist_list_1D.at( sample + "_12VL");
      hs_12VL->Add(temp, "hist");
      sr12VL_leg->AddEntry(temp, sample.c_str());

      // 13VL
      temp = hist_list_1D.at( sample + "_13VL");
      hs_13VL->Add(temp, "hist");
      sr13VL_leg->AddEntry(temp, sample.c_str());

      // 14VL
      temp = hist_list_1D.at( sample + "_14VL");
      hs_14VL->Add(temp, "hist");
      sr14VL_leg->AddEntry(temp, sample.c_str());

      // 15VL
      temp = hist_list_1D.at( sample + "_15VL");
      hs_15VL->Add(temp, "hist");
      sr15VL_leg->AddEntry(temp, sample.c_str());

      // All of L
      temp = hist_list_1D.at( sample + "_1L");
      hs_1L->Add(temp, "hist");
      sr1L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_2L");
      hs_2L->Add(temp, "hist");
      sr2L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_3L");
      hs_3L->Add(temp, "hist");
      sr3L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_4L");
      hs_4L->Add(temp, "hist");
      sr4L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_5L");
      hs_5L->Add(temp, "hist");
      sr5L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_6L");
      hs_6L->Add(temp, "hist");
      sr6L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_7L");
      hs_7L->Add(temp, "hist");
      sr7L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_8L");
      hs_8L->Add(temp, "hist");
      sr8L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_9L");
      hs_9L->Add(temp, "hist");
      sr9L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_10L");
      hs_10L->Add(temp, "hist");
      sr10L_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_11L");
      hs_11L->Add(temp, "hist");
      sr11L_leg->AddEntry(temp, sample.c_str());

      // All of M
      temp = hist_list_1D.at( sample + "_1M");
      hs_1M->Add(temp, "hist");
      sr1M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_2M");
      hs_2M->Add(temp, "hist");
      sr2M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_3M");
      hs_3M->Add(temp, "hist");
      sr3M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_4M");
      hs_4M->Add(temp, "hist");
      sr4M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_5M");
      hs_5M->Add(temp, "hist");
      sr5M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_6M");
      hs_6M->Add(temp, "hist");
      sr6M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_7M");
      hs_7M->Add(temp, "hist");
      sr7M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_8M");
      hs_8M->Add(temp, "hist");
      sr8M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_9M");
      hs_9M->Add(temp, "hist");
      sr9M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_10M");
      hs_10M->Add(temp, "hist");
      sr10M_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_11M");
      hs_11M->Add(temp, "hist");
      sr11M_leg->AddEntry(temp, sample.c_str());

      // All of H
      temp = hist_list_1D.at( sample + "_1H");
      hs_1H->Add(temp, "hist");
      sr1H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_2H");
      hs_2H->Add(temp, "hist");
      sr2H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_3H");
      hs_3H->Add(temp, "hist");
      sr3H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_4H");
      hs_4H->Add(temp, "hist");
      sr4H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_5H");
      hs_5H->Add(temp, "hist");
      sr5H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_6H");
      hs_6H->Add(temp, "hist");
      sr6H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_7H");
      hs_7H->Add(temp, "hist");
      sr7H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_8H");
      hs_8H->Add(temp, "hist");
      sr8H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_9H");
      hs_9H->Add(temp, "hist");
      sr9H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_10H");
      hs_10H->Add(temp, "hist");
      sr10H_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_11H");
      hs_11H->Add(temp, "hist");
      sr11H_leg->AddEntry(temp, sample.c_str());

      // All of UH
      temp = hist_list_1D.at( sample + "_1UH");
      hs_1UH->Add(temp, "hist");
      sr1UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_2UH");
      hs_2UH->Add(temp, "hist");
      sr2UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_3UH");
      hs_3UH->Add(temp, "hist");
      sr3UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_4UH");
      hs_4UH->Add(temp, "hist");
      sr4UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_5UH");
      hs_5UH->Add(temp, "hist");
      sr5UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_6UH");
      hs_6UH->Add(temp, "hist");
      sr6UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_7UH");
      hs_7UH->Add(temp, "hist");
      sr7UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_8UH");
      hs_8UH->Add(temp, "hist");
      sr8UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_9UH");
      hs_9UH->Add(temp, "hist");
      sr9UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_10UH");
      hs_10UH->Add(temp, "hist");
      sr10UH_leg->AddEntry(temp, sample.c_str());
      temp = hist_list_1D.at( sample + "_11UH");
      hs_11UH->Add(temp, "hist");
      sr11UH_leg->AddEntry(temp, sample.c_str());

    }

  hs_1VL->Draw();
  sr1VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/1VL.png");
  hs_2VL->Draw(); 
  sr2VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/2VL.png");
  hs_3VL->Draw(); 
  sr3VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/3VL.png");
  hs_12VL->Draw();
  sr12VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/12VL.png");
  hs_13VL->Draw();
  sr13VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/13VL.png");
  hs_14VL->Draw();
  sr14VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/14VL.png");
  hs_15VL->Draw();
  sr15VL_leg->Draw();
  c1.SaveAs("PNGs/Stacked/15VL.png");

  hs_1L->Draw(); 
  sr1L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/1L.png");
  hs_2L->Draw(); 
  sr2L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/2L.png");
  hs_3L->Draw();
  sr3L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/3L.png");
  hs_4L->Draw(); 
  sr4L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/4L.png");
  hs_5L->Draw(); 
  sr5L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/5L.png");
  hs_6L->Draw(); 
  sr6L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/6L.png");
  hs_7L->Draw(); 
  sr7L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/7L.png");
  hs_8L->Draw(); 
  sr8L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/8L.png");
  hs_9L->Draw(); 
  sr9L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/9L.png");
  hs_10L->Draw(); 
  sr10L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/10L.png");
  hs_11L->Draw(); 
  sr11L_leg->Draw();
  c1.SaveAs("PNGs/Stacked/11L.png");

  hs_1M->Draw(); 
  sr1M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/1M.png");
  hs_2M->Draw(); 
  sr2M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/2M.png");
  hs_3M->Draw();
  sr3M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/3M.png");
  hs_4M->Draw(); 
  sr4M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/4M.png");
  hs_5M->Draw(); 
  sr5M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/5M.png");
  hs_6M->Draw(); 
  sr6M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/6M.png");
  hs_7M->Draw(); 
  sr7M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/7M.png");
  hs_8M->Draw(); 
  sr8M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/8M.png");
  hs_9M->Draw(); 
  sr9M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/9M.png");
  hs_10M->Draw(); 
  sr10M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/10M.png");
  hs_11M->Draw(); 
  sr11M_leg->Draw();
  c1.SaveAs("PNGs/Stacked/11M.png");

  hs_1H->Draw(); 
  sr1H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/1H.png");
  hs_2H->Draw(); 
  sr2H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/2H.png");
  hs_3H->Draw();
  sr3H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/3H.png");
  hs_4H->Draw(); 
  sr4H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/4H.png");
  hs_5H->Draw(); 
  sr5H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/5H.png");
  hs_6H->Draw(); 
  sr6H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/6H.png");
  hs_7H->Draw(); 
  sr7H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/7H.png");
  hs_8H->Draw(); 
  sr8H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/8H.png");
  hs_9H->Draw(); 
  sr9H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/9H.png");
  hs_10H->Draw(); 
  sr10H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/10H.png");
  hs_11H->Draw(); 
  sr11H_leg->Draw();
  c1.SaveAs("PNGs/Stacked/11H.png");

  hs_1UH->Draw(); 
  sr1UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/1UH.png");
  hs_2UH->Draw(); 
  sr2UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/2UH.png");
  hs_3UH->Draw();
  sr3UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/3UH.png");
  hs_4UH->Draw(); 
  sr4UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/4UH.png");
  hs_5UH->Draw(); 
  sr5UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/5UH.png");
  hs_6UH->Draw(); 
  sr6UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/6UH.png");
  hs_7UH->Draw(); 
  sr7UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/7UH.png");
  hs_8UH->Draw(); 
  sr8UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/8UH.png");
  hs_9UH->Draw(); 
  sr9UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/9UH.png");
  hs_10UH->Draw(); 
  sr10UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/10UH.png");
  hs_11UH->Draw(); 
  sr11UH_leg->Draw();
  c1.SaveAs("PNGs/Stacked/11UH.png");

}
