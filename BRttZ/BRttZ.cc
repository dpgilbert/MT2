// C++
#include <iostream>

// ROOT
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TFile.h"

// Tools
#include "mt2tree_ttz.h"

using namespace std;

void loop (const TTree * in_tree, const char * file_name)
{
  
  // Prepare input files and tree for loop
  int nEvents = in_tree->GetEntries();
  unsigned int nMax = nEvents;
  
  // initialize table
  float counts [6][5] = {0.0}; // 6 top topologies, 5 Z topologies

  TTree* input = (TTree*) in_tree->Clone();
  mt2tree_ttz mt2_tree;
  mt2_tree.Init(input); // Branch boilerplate etc.

  cout << "Running on " << nMax << " events" << endl;
  
  for( unsigned int event = 0; event < nMax; event++)
    {
      if ( (event+1) % 10000 == 0) cout << "Processing event " << event+1 << ", " << (100. * event) / nMax << "% complete" << endl;
      
      mt2_tree.GetEntry(event);
      
      const float w_ = 35.9 * mt2_tree.evt_scale1fb;
      
      const int* genIDs = mt2_tree.genStat23_pdgId;
      const int* sourceIDs = mt2_tree.genStat23_sourceId;
      const int ngen_ = mt2_tree.ngenStat23;

      // 0 for LL, 1 for LC, 2 for CC, 3 for Llep, 4 for Clep, 5 for leplep
      int topIndex = -1;
      // 0 for light, 1 for charm, 2 for bottom, 3 for nu, 4 for lep
      int ZIndex = -1;

      int nlightTop = 0, ncharmTop = 0, nlepTop = 0, nlightZ = 0, ncharmZ = 0, nbotZ = 0;
      bool foundH = false;
      for (int i = 0; i < ngen_ && !foundH; i++)
	{
	  
	  const int ID = abs(genIDs[i]);
	  if (ID == 25)
	    {
	      foundH = true;
	      continue;
	    }
	  if (ID == 23 || ID == 6 || ID == 12 || ID == 14 || ID == 16) continue;
	  const int sID = abs(sourceIDs[i]);

	  if (ID < 4) // count lights
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
	      else if (sID == 6)
		{
		  nlepTop++;
		}
	    }	  
	}

      if (foundH) continue;

      // Sometimes particles decay directly to final state particles with status codes 1 or 2 rather than 23. This is almost always
      // a leptonic decay. If we don't have 2 daughters, assume that the ones we don't have are leptons.

      if (nlightTop + ncharmTop + nlepTop == 0) nlepTop = 2;
      else if (nlightTop + ncharmTop + nlepTop == 1) nlepTop++;

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
	  ZIndex = 0;
	}
      else if (ncharmZ == 2)
	{
	  ZIndex = 1;
	}
      else if (nbotZ == 2)
	{
	  ZIndex = 2;
	}
      else if (mt2_tree.ngenNuFromZ == 2)
	{
	  ZIndex = 3;
	}
      else if (mt2_tree.ngenLepFromZ == 2)
	{
	  ZIndex = 4;
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
      
    }

  const char * Zheaders [5] = {"LL Z\t\t", "CC Z\t\t", "BB Z\t\t", "NuNu Z\t\t", "ll Z\t\t"};

  cout << "\t\tLL Top\t\tLC Top\t\tLl Top\t\tCC Top\t\tCl Top\t\tll Top" << endl;
  for (int a = 0; a < 5; a++)
    {
      cout << Zheaders[a];
      for (int b = 0; b < 6; b++)
	{
	  cout << fixed << setprecision(5) << counts[b][a] << "\t\t";
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
  loop(in_tree, file_name);
}
