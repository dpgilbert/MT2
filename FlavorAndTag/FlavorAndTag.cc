// C++
#include <iostream>

// ROOT
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TFile.h"

// Tools
#include "../../MT2CORE/mt2tree.h"

using namespace std;

void loop (const TTree * in_tree, const char * file_name)
{
  
  // Prepare input files and tree for loop
  int nEvents = in_tree->GetEntries();
  unsigned int nMax = nEvents;
  
  /*
   * Book Histograms
   */

  TH1::SetDefaultSumw2(true);

  TH1F h_lf("h_light_fakes", "Weighted Light Fake Multiplicity Distribution;Multiplicity;Count @ 35.9 fb^{-1}", 5, 0, 5);
  TH1F h_cf("h_charm_fakes", "Weighted Charm Fake Multiplicity Distribution;Multiplicity;Count @ 35.9 fb^{-1}", 5, 0, 5);
  TH1F h_true("h_true_tags", "Weighted True Tag Multiplicity Distribution;Multiplicity;Count @ 35.9 fb^{-1}", 5, 0, 5);
  TH1F h_tagged_pt("h_tagged_pt", "Weighted Tagged Jet p_{T} Distribution;p_{T} (GeV);Count @ 35.9 fb^{-1}", 10, 20, 120);
  TH1F h_trueb_pt("h_trueb_pt", "Weighted p_{T} Distribution of all b-Jets, Tagged and Untagged;p_{T} (GeV);Count @ 35.9 fb^{-1}", 10, 20, 120);
  TH1F h_trueb_eta("h_trueb_eta", "Weighted |#eta| Distribution of all b-Jets, Tagged and Untagged;|#eta|;Count @ 35.9 fb^{-1}", 10, 0, 5);

  TTree* input = (TTree*) in_tree->Clone();
  mt2tree mt2_tree;
  mt2_tree.Init(input); // Branch boilerplate etc.

  double fix_evtscale1fb = 0;
  if (file_name[0] == 'T') // signal, prep for evt_scale1fb manual calculation
    {
      TString sig_file(file_name);
      TString sig_sample = file_name[1] == '1' ? sig_file(0,6) : sig_file(0,4); // T1xxxx or T2xx
      TFile* f_nsig_weights = new TFile(Form("../../babymaker/data/nsig_weights_%s.root",sig_sample.Data()));
      TH2D* h_sig_nevents = (TH2D*) f_nsig_weights->Get("h_nsig");
      int binx = h_sig_nevents->GetXaxis()->FindBin(mt2_tree.GenSusyMScan1);
      int biny = h_sig_nevents->GetYaxis()->FindBin(mt2_tree.GenSusyMScan2);
      double nevents = h_sig_nevents->GetBinContent(binx,biny);
      fix_evtscale1fb = 35900 / nevents;
    }

  cout << "Running on " << nMax << " events" << endl;
  
  int passb = 0, passc = 0, passl = 0;
  int totalb = 0, totalc = 0, totall = 0;

  for( unsigned int event = 0; event < nMax; event++)
    {
      if ( (event+1) % 10000 == 0) cout << "Processing event " << event+1 << ", " << (100. * event) / nMax << "% complete" << endl;
      
      mt2_tree.GetEntry(event);
      
      // test ? sig : background
      const float w_ = (file_name[0] == 'T') ? fix_evtscale1fb * mt2_tree.evt_xsec : 35.9 * mt2_tree.evt_scale1fb;
      
      //float mt2_ = mt2_tree.mt2;
      //float ht_ =  mt2_tree.ht;
      //float met_ = mt2_tree.met_pt;
      //      const int nj_ = mt2_tree.nJet30;
      //int nb_ = mt2_tree.nBJet20;

      const int njet_ = mt2_tree.njet;

      const float* jet_pt_ = mt2_tree.jet_pt;
      const float* jet_eta_ = mt2_tree.jet_eta;

      const int * flav_ = mt2_tree.jet_mcFlavour;
      const float * csv_ = mt2_tree.jet_btagCSV;

      const float MEDIUM_WORKING_POINT = 0.8484; 


      int true_tag = 0, charm_fake = 0, light_fake = 0;
      for (int i = 0; i < njet_; i++)
	{
	  const int flavor_ = abs(flav_[i]);
	  if (flavor_ == 21 || flavor_ < 4)
	    {
	      //if (flavor_ == 0) cout << "0 flavor for jet " << i << ", xsec = " << mt2_tree.evt_xsec << ", run:lumi:evt = " << mt2_tree.run << ":" << mt2_tree.lumi << ":" << mt2_tree.evt << endl;
	      totall++;
	      if (csv_[i] > MEDIUM_WORKING_POINT && jet_pt_[i] >= 20.0)
		{
		  light_fake++;
		  h_tagged_pt.Fill(jet_pt_[i], w_);
		}
	    }
	  else if (flavor_ == 4)
	    {
	      totalc++;
	      if (csv_[i] > MEDIUM_WORKING_POINT && jet_pt_[i] >= 20.0)
		{
		  charm_fake++;
		  h_tagged_pt.Fill(jet_pt_[i], w_);
		}
	    }
	  else if (flavor_ == 5)
	    {
	      totalb++;
	      h_trueb_pt.Fill(jet_pt_[i], w_);
	      h_trueb_eta.Fill(jet_eta_[i], w_);
	      if (csv_[i] > MEDIUM_WORKING_POINT && jet_pt_[i] >= 20.0)
		{
		  true_tag++; 
		  h_tagged_pt.Fill(jet_pt_[i], w_);
		}
	    }
	  else
	    {
	      cout << "anomalous jet flavor " << abs(flav_[i]) << " in event " << event << "." << endl;	      	      
	    }
	  
	  //      if (true_tag >= 3) cout << "3+ true tags in event " << event << ", xsec = " << mt2_tree.evt_xsec << ", run:lumi:evt = " << mt2_tree.run << ":" << mt2_tree.lumi << ":" << mt2_tree.evt << endl;
	  
	} // jet loop  
	     
      h_lf.Fill(light_fake, w_);
      h_cf.Fill(charm_fake, w_);
      h_true.Fill(true_tag, w_);
      
      passl += light_fake;
      passc += charm_fake;
      passb += true_tag;
      
    } // event loop
  
  TString full_name(file_name);
  TString clean_name = full_name(full_name.Last('/')+1,full_name.Length());
  // save plots
  TFile outfile (clean_name.Prepend("hists/"),"RECREATE");
  outfile.cd();
  h_lf.Write();
  h_cf.Write();
  h_true.Write();
  h_tagged_pt.Write();
  h_trueb_pt.Write();
  h_trueb_eta.Write();
  outfile.Close();

  cout << "light jet tag rate = " << (100.0 * passl) / totall << endl;
  cout << "charm jet tag rate = " << (100.0 * passc) / totalc << endl;
  cout << "bottom jet tag rate = " << (100.0 * passb) / totalb << endl;

}
    

int main (const int argc, const char ** argv) 
{
  if (argc == 1) {cout << "Need an input file." << endl; return 0;}
  const char * file_name = argv[1];
  TFile* infile = TFile::Open(file_name);
  TTree * in_tree = (TTree *) infile->Get("mt2");
  loop(in_tree, file_name);
}
