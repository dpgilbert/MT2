// A looper to determine which files are contributing to the final QCD MT2 distributions

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TH1.h"

#include "../../CORE/Tools/utils.h"

#include "../../MT2CORE/mt2tree.h"
#include "../../MT2CORE/sigSelections.h"

#include "QCDfault.h"

using namespace std;

enum origin
  {
    ht1000to1500, // 1207
    ht1500to2000, // 119.9
    ht2000toInf, // 25.24
    ht300to500, // 347700
    ht500to700, // 32100
    ht700to1000 // 6831
  };

int GetOriginFile (float evt_xsec)
{
  if ( fabs(evt_xsec / 347700 - 1 ) < 0.001 ) return ht300to500;
  if ( fabs(evt_xsec / 32100 - 1 ) < 0.001 ) return ht500to700;
  if ( fabs(evt_xsec / 6831 - 1 ) < 0.001 ) return ht700to1000;
  if ( fabs(evt_xsec / 1207 - 1 ) < 0.001 ) return ht1000to1500;
  if ( fabs(evt_xsec / 119.9 - 1 ) < 0.001 ) return ht1500to2000;
  if ( fabs(evt_xsec / 25.24 - 1 ) < 0.001 ) return ht2000toInf;
  cout << "Impossible cross section: " << evt_xsec << endl;
  return -1;
}

int main (int argc, char ** argv)
{
  TFile * tf = TFile::Open("/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/SkimmedMC/qcd_ht.root");
  TTree *tree = (TTree*)tf->Get("mt2");
  if ( tree == NULL) 
    {
      cout << "tree is null" << endl;
      return 0;
    }
  unsigned int nMax = tree->GetEntries();
  mt2tree mt2_tree;
  mt2_tree.Init(tree);

  vector<SR> signal_regions = mt2::getSignalRegions2016();
  map< SR*, TH1F* > hists300;
  map< SR*, TH1F* > hists500;
  map< SR*, TH1F* > hists700;
  map< SR*, TH1F* > hists1000;
  map< SR*, TH1F* > hists1500;
  map< SR*, TH1F* > hists2000;
  
  TH1::SetDefaultSumw2(true);
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, from Gen H_{T} 300-500;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists300[ reg_ptr ] = temp;
    }
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, from Gen H_{T} 500-700;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists500[ reg_ptr ] = temp;
    }
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, From 300to500;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists300[ reg_ptr ] = temp;
    }
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, from Gen H_{T} 700-1000;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists700[ reg_ptr ] = temp;
    }
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, from Gen H_{T} 1000-1500;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists1000[ reg_ptr ] = temp;
    }
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, from Gen H_{T} 1500-2000;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists1500[ reg_ptr ] = temp;
    }
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2}, from Gen H_{T} 2000+;M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists2000[ reg_ptr ] = temp;
    }

  cout << "looping over " << nMax << " events" << endl;

  for (unsigned int event = 0; event < nMax; event++)
    {
      mt2_tree.GetEntry(event);
      
      // njets, nbjets, ht, met are only important ones because the events we're running on are skimmed, but PassesSelection complains if we omit some
      float w_ = mt2_tree.evt_scale1fb;
      float mt2_ = mt2_tree.mt2;
      float ht_ = mt2_tree.ht;
      float met_ = mt2_tree.met_pt;
      int nj_ = mt2_tree.nJet30;
      int nb_ = mt2_tree.nBJet20;
      // unimportant ones
      float j1pt_ = mt2_tree.jet1_pt;
      float j2pt_ = mt2_tree.jet2_pt;
      int nlep_ = 0; // must be in order to get here
      float deltaPhiMin_ = mt2_tree.deltaPhiMin;
      float diffMetMhtOverMet_ = mt2_tree.diffMetMht / met_;

      float evt_xsec = mt2_tree.evt_xsec;
      int run_ = mt2_tree.run;
      int lumi_ = mt2_tree.lumi;
      int evt_ = mt2_tree.evt;

      map< string, float > values;
      values["mt2"] = mt2_;
      values["ht"] = ht_;
      values["njets"] = nj_;
      values["nbjets"] = nb_;
      values["met"] = met_;
      values["j1pt"] = j1pt_;
      values["j2pt"] = j2pt_;
      values["nlep"] = nlep_;
      values["deltaPhiMin"] = deltaPhiMin_;
      values["diffMetMhtOverMet"] = diffMetMhtOverMet_;
      
      map< SR*, TH1F* >* hists;      
      string which_file = "";
      switch (GetOriginFile(evt_xsec))
	{
	case ht300to500: hists = &hists300; which_file = "300to500"; break;
	case ht500to700: hists = &hists500; which_file = "500to700"; break;
	case ht700to1000: hists = &hists700; which_file = "700to1000"; break;
	case ht1000to1500: hists = &hists1000; which_file = "1000to1500"; break;
	case ht1500to2000: hists = &hists1500; which_file = "1500to2000"; break;
	case ht2000toInf: hists = &hists2000; which_file = "2000toInf"; break;
	default: cout << "evt_xsec took impossible value: " << evt_xsec << ", aborting..." << endl; return 0;
	}

      for (map< SR*, TH1F* >::iterator it_h = hists->begin(); it_h != hists->end(); ++it_h)
	{
	  SR* sr_ptr = (*it_h).first;
	  if (sr_ptr->PassesSelection(values))
	    {	     
	      (*hists)[sr_ptr]->Fill(mt2_, w_);
	      cout << sr_ptr->GetName() << ", from" << which_file << "; mt2 = " << mt2_ << ", run:lumi:evt = "
		   << run_ << ":" << lumi_ << ":" << evt_ << endl;
	    }
	}
    }

  TFile outfile300( "/home/users/dpg/MT2AnalysisEdit/MyCode/QCDfault/output/hists300to500.root", "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists300.begin(); it_h != hists300.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile300.Close();

  TFile outfile500( "/home/users/dpg/MT2AnalysisEdit/MyCode/QCDfault/output/hists500to700.root", "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists500.begin(); it_h != hists500.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile500.Close();

  TFile outfile700( "/home/users/dpg/MT2AnalysisEdit/MyCode/QCDfault/output/hists700to1000.root", "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists700.begin(); it_h != hists700.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile700.Close();

  TFile outfile1000( "/home/users/dpg/MT2AnalysisEdit/MyCode/QCDfault/output/hists1000to1500.root", "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists1000.begin(); it_h != hists1000.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile1000.Close();

  TFile outfile1500( "/home/users/dpg/MT2AnalysisEdit/MyCode/QCDfault/output/hists1500to2000.root", "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists1500.begin(); it_h != hists1500.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile1500.Close();

  TFile outfile2000( "/home/users/dpg/MT2AnalysisEdit/MyCode/QCDfault/output/hists2000toInf.root", "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists2000.begin(); it_h != hists2000.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile2000.Close();

}
