// C++
#include <iostream>

// ROOT
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TFile.h"

#include "mt2tree_ttz.h"

using namespace std;

void loop (const TTree * in_tree, const char * file_name, const int param_max)
{
  
  // Prepare input files and tree for loop
  int nEvents = in_tree->GetEntries();
  unsigned int nMax = nEvents;
  if (param_max > 0) 
    {
      if ( (unsigned int) param_max < nMax) nMax = param_max;
    }
  
  // initialize table
  float counts [6][5] = {0.0}; // 6 top topologies, 5 Z topologies

  TTree* input = (TTree*) in_tree->Clone();
  mt2tree_ttz mt2_tree;
  mt2_tree.Init(input); // Branch boilerplate etc.

  cout << "Running on " << nMax << " events" << endl;
  
  for (unsigned int event = 0; event < nMax; event++)
    {
      if ( (event+1) % 10000 == 0) cout << "Processing event " << event+1 << ", " << (100. * event) / nMax << "% complete" << endl;
      
      mt2_tree.GetEntry(event);
      
      const float w_ = 35.9 * mt2_tree.evt_scale1fb;
      
      const int ngen_ = mt2_tree.ngenStat23;
      
      // 0 for LL, 1 for LC, 2 for CC, 3 for Llep, 4 for Clep, 5 for leplep
      int topIndex = -1;
      // 0 for light, 1 for charm, 2 for bottom, 3 for nu, 4 for lep
      int ZIndex = -1;
      
      int nlightTop = 0, ncharmTop = 0, nlepTop = 0, nlightZ = 0, ncharmZ = 0, nbotZ = 0;
      bool foundH = false;

      for (int i = 0; i < ngen_ && !foundH; i++) // loop over gen particles
	{
	  const unsigned int ID = abs(mt2_tree.genStat23_pdgId[i]);
	  if (ID == 25)
	    {
	      foundH = true;
	      continue;
	    }
	  const unsigned int sID = abs(mt2_tree.genStat23_sourceId[i]);

	  if (ID < 3) // count lights
	    {
	      if (sID == 23) 
		{
		  nlightZ++;
		}
	      else if (sID == 6)
		{
		  nlightTop++;
		}
	    }
	  else if (ID == 3) // 2 lights from W > ud, 1 light from W > cs, don't want to count strange as light for Tops since that W should be counted as a charm
	    {
	      if (sID == 23)
		{
		  nlightZ++;
		}
	    }
	  else if (ID == 4) // count charms
	    {
	      if (sID == 23)
		{
		  ncharmZ++;
		}
	      else if (sID == 6)
		{
		  ncharmTop++;
		}
	    }
	  else if (ID == 5) // don't count b's from top, but do count Z > bb
	    {
	      if (sID == 23)
		{
		  nbotZ++;
		}
	    }
	  else if (ID == 11 || ID == 13 || ID == 15) // don't need to count leptons for Z, it's in the tree
	    {
	      if (sID == 6)
		{
		  nlepTop++;
		}
	    }	  
	} // end loop over gen particles
      
      if (foundH) continue;
      
      // Sometimes particles decay directly to final state particles with status codes 1 or 2 rather than 23. This is almost always
      // a leptonic decay. If we don't have 2 daughters, assume that the ones we don't have are leptons.

      if (nlightTop + ncharmTop + nlepTop == 0) nlepTop = 2;
      else if (nlightTop < 2 && ncharmTop + nlepTop == 1) nlepTop++;
      
      if (ncharmTop == 1)
	{
	  if (nlightTop > 0 && nlepTop == 0) // sometimes get many light partons from top decay
	    {
	      topIndex = 1; // light charm
	    }
	  else if (nlepTop == 1)
	    {
	      topIndex = 4; // charm lep
	    }
	  else 
	    {
	      cout << "Something went wrong with tops in event " << event << endl;
	    }
	}
      else if (ncharmTop == 2)
	{
	  topIndex = 3; // charm charm
	}
      else if (ncharmTop == 0)
	{
	  if (nlepTop == 1 && nlightTop > 0)
	    {
	      topIndex = 2; // light lep
	    }
	  else if (nlepTop == 0 && nlightTop > 0)
	    {
	      topIndex = 0; // light light
	    }
	  else if (nlepTop == 2)
	    {
	      topIndex = 5; // lep lep
	    }
	}
      
      if (nlightZ == 2)
	{
	  ZIndex = 0; // light light
	}
      else if (ncharmZ == 2)
	{
	  ZIndex = 1; // charm charm
	}
      else if (nbotZ == 2)
	{
	  ZIndex = 2; // bot bot
	}
      else if (mt2_tree.ngenNuFromZ == 2)
	{
	  ZIndex = 3; // nu nu
	}
      else if (mt2_tree.ngenLepFromZ == 2)
	{
	  ZIndex = 4; // lep lep
	}
      else 
	{
	  cout << "Something went wrong with Z in event " << event << endl;
	}
      
      if (topIndex >= 0 && ZIndex >= 0)
	{
	  counts[topIndex][ZIndex] += w_;
	}
      else 
	{
	  cout << "Error setting indices in event " << event << ": topIndex = " << topIndex << ", ZIndex = " << ZIndex << endl;
	  cout << "nlightTop = " << nlightTop << endl;
	  cout << "ncharmTop = " << ncharmTop << endl;
	  cout << "nlepTop = " << nlepTop << endl;
	  cout << "nlightZ = " << nlightZ << endl;
	  cout << "ncharmZ = " << ncharmZ << endl;
	  cout << "nbotZ = " << nbotZ << endl;
	  cout << "ngenNuFromZ = " << mt2_tree.ngenNuFromZ << endl;
	  cout << "ngenLepFromZ = " << mt2_tree.ngenLepFromZ << endl;
	}
      
    } // end event loop
 
  const char * Zheaders [5] = {"LL Z\t\t", "CC Z\t\t", "BB Z\t\t", "NuNu Z\t\t", "ll Z\t\t"};
  
  float total = 0;
  
  cout << "\t\tLL Top\t\tLC Top\t\tLl Top\t\tCC Top\t\tCl Top\t\tll Top" << endl;
  for (int a = 0; a < 5; a++)
    {
      cout << Zheaders[a];
      for (int b = 0; b < 6; b++)
	{
	  cout << fixed << setprecision(5) << counts[b][a] << "\t\t";
	  total+=counts[b][a];
	}
      cout << endl;
    }
  cout << "******" << endl;
  cout << "\t\tLL Top\t\tLC Top\t\tLl Top\t\tCC Top\t\tCl Top\t\tll Top" << endl;
  for (int a = 0; a < 5; a++)
    {
      cout << Zheaders[a];
      for (int b = 0; b < 6; b++)
	{
	  cout << fixed << setprecision(5) << 100 * counts[b][a] / total << "\%\t";
	}
      cout << endl;
    }
}
    

int main (const int argc, const char ** argv) 
{
  if (argc == 1) {cout << "Need an input file." << endl; return 0;}
  const char * file_name = argv[1];
  TFile* infile = TFile::Open(file_name);
  TTree * in_tree = (TTree *) infile->Get("mt2");
  int param_max = argc == 3 ? atoi(argv[2]) : -1;
  loop(in_tree, file_name, param_max);
}
