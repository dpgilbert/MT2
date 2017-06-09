// A looper to produce SR plots from MC and compare them to data driven estimates

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

using namespace std;

int main (int argc, char ** argv)
{
  if (argc < 2)
    {
      cout << "Which sample? Usage: ./DDvsMC <sample>" << endl;
      return 0;
    }

  const char * sample = argv[1];
  const TString mc_input_name = Form("/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/SkimmedMC/%s.root",sample);
  TFile * tf = TFile::Open(mc_input_name);
  TTree *tree = (TTree*)tf->Get("mt2");
  if ( tree == NULL) 
    {
      cout << "tree is null" << endl;
      return 0;
    }
  unsigned int nMax = tree->GetEntries(); // this line segfaults
  mt2tree mt2_tree;
  mt2_tree.Init(tree);

  vector<SR> signal_regions = mt2::getSignalRegions2016();
  map< SR*, TH1F* > hists;
  TH1::SetDefaultSumw2(true);
  for (vector<SR>::iterator it_sr = signal_regions.begin(); it_sr != signal_regions.end(); ++it_sr)
    {
      SR region = *it_sr;
      string name = region.GetName();
      float* mt2bins = region.GetMT2Bins();
      int nbins = region.GetNumberOfMT2Bins();
      TH1F* temp = new TH1F( name.c_str() , (name+" M_{T2};M_{T2} (GeV);Count / fb").c_str() , nbins , mt2bins );
      // get pointer to SR from iterator by taking vector array and adding iterator offset
      SR* reg_ptr = signal_regions.data() + (it_sr-signal_regions.begin());
      hists[ reg_ptr ] = temp;
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

      for (map< SR*, TH1F* >::iterator it_h = hists.begin(); it_h != hists.end(); ++it_h)
	{
	  SR* sr_ptr = (*it_h).first;
	  if (sr_ptr->PassesSelection(values))
	    {	     
	      hists[sr_ptr]->Fill(mt2_, w_);
	    }
	}
    }

  TString out_name = Form("/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/output/%s.root", sample);
  TFile outfile( out_name, "RECREATE");
  for (map< SR*, TH1F* >::iterator it_h = hists.begin(); it_h != hists.end(); ++it_h)
    {
      TH1F* toWrite = (TH1F*) (*it_h).second;
      toWrite->Write();
    }
  outfile.Close();

}
