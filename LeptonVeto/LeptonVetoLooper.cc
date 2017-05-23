// C++
#include <iostream>
#include <vector>
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

//#include "RooRealVar.h"
//#include "RooDataSet.h"

// Tools
#include "../../CORE/Tools/utils.h"
#include "../../CORE/Tools/goodrun.h"
#include "../../CORE/Tools/dorky/dorky.h"
#include "../../CORE/Tools/badEventFilter.h"

#include "../../MT2CORE/mt2tree.h"

using namespace std;
//using namespace mt2;
using namespace duplicate_removal;

void PlotLoop (const TChain& chain, const string& output_file_name)
{
  // first make absolutely sure we're not overwriting an input file like an idiot
  if (output_file_name.find("userdata") != string::npos) 
    {
      cout << "Output file looks dangerous." << endl;
      return;
    }
  
  // Prepare input files and tree for loop
  int nEvents = chain.GetEntries();
  unsigned int nMax = nEvents;
  
  int nee=0;
  int nmm=0;
  int ntt=0;
  int net=0;
  int nmt=0;
  int nem=0;


  TTree *tree = (TTree*)chain.Clone("mt2");
  mt2tree mt2_tree;
  mt2_tree.Init(tree); // Branch boilerplate etc.

  cout << "Running on " << nMax << " events" << endl;
  
  for( unsigned int event = 0; event < nMax; event++)
    {
      if ( (event+1) % 10000 == 0) cout << "Processing event " << event+1 << endl;
      
      mt2_tree.GetEntry(event);
      
      float mt2_ = mt2_tree.mt2;
      float ht_ =  mt2_tree.ht;
      float dphi_ = mt2_tree.deltaPhiMin;
      float diff_ = mt2_tree.diffMetMht;
      float met_ = mt2_tree.met_pt;
      float dom_ = diff_/met_;
      int nj_ = mt2_tree.nJet30;
      int lep_veto_index_ = mt2_tree.nMuons10 + mt2_tree.nElectrons10 + mt2_tree.nPFLep5LowMT + /*tau*/mt2_tree.nPFHad10LowMT;

      // IMPLEMENT DATA LOGIC

      // Apply cuts
      bool PassTrigger = ( (ht_ > 1000 && met_ > 30) || (ht_ > 250 && met_ > 250) );
      bool PassNJ = ( nj_ > 0 );
      bool PassDphi = ( dphi_ > 0.3 );
      bool PassDom = ( dom_ < 0.5 );
      bool PassLep = ( lep_veto_index_ < 1 );
      bool PassMT2 = ( nj_ < 2 || mt2_ > 400 || (mt2_ > 200 && ht_ < 1500) );

      // only care about events that manage to pass all other cuts
      if (! (PassTrigger && PassNJ && PassDphi && PassDom && PassMT2 && PassLep) ) continue;


      // So we passed every selection, including the lepton veto, despite running on an event including leptons
      // Let's see what the leptons in this event were
      
      int lep1_pdg = 0;
      int lep2_pdg = 0;

      if (mt2_tree.ngenLep + mt2_tree.ngenTau != 2) 
	{
	  cout << "Weird event: " << event << endl;
	  continue;
	}

      if (mt2_tree.ngenLep == 1)
	{
	  lep1_pdg = mt2_tree.genLep_pdgId[0];
	  lep2_pdg = mt2_tree.genTau_pdgId[0];
	}
      if (mt2_tree.ngenLep == 2)
	{
	  lep1_pdg = mt2_tree.genLep_pdgId[0];
	  lep2_pdg = mt2_tree.genLep_pdgId[1];
	}
      if (mt2_tree.ngenTau == 2)
	{
	  lep1_pdg = mt2_tree.genTau_pdgId[0];
	  lep2_pdg = mt2_tree.genTau_pdgId[1];
	}

      bool e = false;
      bool mu = false;
      bool tau = false;

      if (lep1_pdg == 11 || lep1_pdg == -11) e = true;
      if (lep2_pdg == 11 || lep2_pdg == -11) e = true;

      if (lep1_pdg == 13 || lep1_pdg == -13) mu = true;
      if (lep2_pdg == 13 || lep2_pdg == -13) mu = true;
      
      if (lep1_pdg == 15 || lep1_pdg == -15) tau = true;
      if (lep2_pdg == 15 || lep2_pdg == -15) tau = true;

      if (e && mu) 
	{
	  nem++; 
	  cout << "event " << event << " lost e and mu" << endl;
	  continue;
	}
      if (e && tau) 
	{
	  net++; 
	  cout << "event " << event << " lost e and tau" << endl;
	  continue;
	}
      if (mu && tau) 
	{
	  nmt++; 
	  cout << "event " << event << " lost mu and tau" << endl;
	  continue;
	}
      if (e) 
	{
	  nee++; 
	  cout << "event " << event << " lost e and e" << endl;
	  continue;
	}
      if (mu) 
	{
	  nmm++; 
	  cout << "event " << event << " lost mu and mu" << endl;
	  continue;
	}
      if (tau) 
	{
	  ntt++; 
	  cout << "event " << event << " lost tau and tau" << endl;
	  continue;
	}
      
    }

  int total = nem + net + nmt + nee + nmm + ntt;

  cout << "total double lost lepton rate: " << (double) total / nMax << endl;
  cout << "ee misId fraction is: " << (double) nee / total << endl;
  cout << "mumu misId fraction is: " << (double) nmm / total << endl;
  cout << "tautau misId fraction is: " << (double) ntt / total << endl;
  cout << "emu misId fraction is: " << (double) nem / total << endl;
  cout << "etau misId fraction is: " << (double) net / total << endl;
  cout << "mutau misId fraction is: " << (double) nmt / total << endl;
}
    

int main (const int argc, const char ** run_params) // first file is output, others are input
{
  if (argc > 1)
    {
      return 1;
    }
  else
    { 
      TChain chain("mt2");
      string next_line;
      string output_file_name = "histos.root";
      bool input_given = false;
      while (getline(cin, next_line)) // only need first file
	{
	  if (next_line.find(".root") == string::npos) // output file name
	    {	  
	      output_file_name = next_line+".root";
	      cout << "Using " << output_file_name << " as output file name." << endl;
	    }
	  else
	    {
	      input_given = true;
	      chain.Add(next_line.c_str());
	      cout << "Added input file " << next_line << " to the TChain." << endl;
	  }
      }
      if (input_given)
	{
	  PlotLoop(chain,output_file_name);
	  return 1;
	}
      else
	{
	  cout << "List output file names without .root along with input file names including .root" << endl;
	  return 0;
	}
    }


}
