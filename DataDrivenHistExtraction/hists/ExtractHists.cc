// Read a table and output TH1s

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TH1.h"
#include "TFile.h"

using namespace std;

struct bin
{
  float min;
  float zdy;
  float zdyerr;
  float ll;
  float llerr;
  float qcd;
  float qcderr;
  float zgj;
  float zgjerr;
};

bool bin_sort (bin A, bin B)
{
  return A.min < B.min;
}

int main (int argc, char ** argv)
{
  const char * inputFile = "";
  for (int i = 1; i < argc; i++)
    {
      filebuf fb;
      inputFile = argv[i];
      if (fb.open(inputFile,ios::in))
	{
	  istream input(&fb);
	  TString contents;
	  contents.ReadFile(input);
	  TObjArray * tokens = contents.Tokenize("\n\t ");

	  vector<bin> bins;
	  
	  for (int j = 0; j < tokens->GetEntries(); j++)
	    {
	      TString tokenj = ((TObjString *) (tokens->At(j)))->String();	      
	      if ( tokenj.EqualTo("bin") )
		{
		  bin thisBin;
		  TString bin_string = ((TObjString *) (tokens->At(j+1)))->String();
		  TString min_string = bin_string(1, bin_string.Index('t')-1); // start after the m, go until the t in "to"
		  float min = min_string.Atof(); 
		  thisBin.min = min;
		  thisBin.zdy = ((TObjString *) (tokens->At(j+3)))->String().Atof();
		  thisBin.zdyerr = ((TObjString *) (tokens->At(j+4)))->String().Atof();
		  thisBin.ll = ((TObjString *) (tokens->At(j+6)))->String().Atof();
		  thisBin.llerr = ((TObjString *) (tokens->At(j+7)))->String().Atof();
		  thisBin.qcd = ((TObjString *) (tokens->At(j+9)))->String().Atof();
		  thisBin.qcderr = ((TObjString *) (tokens->At(j+10)))->String().Atof();
		  thisBin.zgj = ((TObjString *) (tokens->At(j+12)))->String().Atof();
		  thisBin.zgjerr = ((TObjString *) (tokens->At(j+13)))->String().Atof();
		  j += 13;
		  bins.push_back(thisBin);
		}
	    }

	  // Now find the appropriate output file
	  // Form of file name is [header]/HTmintomax_jmintomax_bmintomax_m[t2]mintomax.txt
	  // we want a separate file for each HT-jet-b triple, but to print each mt2 bin in that file
	  TString in_name(inputFile);
	  int last_slash = in_name.Last('/');
	  TString clean_name = in_name(last_slash+1, in_name.Length());

	  // sort bins and make histograms
	  sort(bins.begin(), bins.end(), bin_sort);

	  // need to handle the special case of max of last bin
	  float max = 1500.0;
	  // 1800 is the actual max used by sigSelections.cc for UH and Supers; 1500 is used for VL, L, M, and H.
	  // UH has HT > 1500, so we can use the fact that the file name will be HT15.... to distinguish
	  // Also take this opportunity to add an empty 200-400 bin for division with MC
	  if ( clean_name(2) == '1' && clean_name(3) == '5' ) // UH
	    {
	      // THIS LOGIC LEAVES OUT LOOSE SUPER SIGNAL REGIONS...but no super signal regions are present in tables

	      max = 1800.0; 
	      bin empty = {200.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	      bins.insert(bins.begin(), empty);
	    }
	  //else VL, L, M, H
	  
	  int nbins = bins.size();
	  float bin_mins [nbins+1];
	  for (vector<bin>::iterator it = bins.begin(); it != bins.end(); ++it)
	    {
	      int idx = it - bins.begin();
	      bin_mins[idx] = (*it).min;	      
	    }
	  bin_mins[nbins] = max;
	  
	  fb.close();
	  tokens->Delete();
	  
	  for (int x = 0; x < nbins+1; x++)
	    {
	      cout << bin_mins[x] << endl;
	    }
	  cout << "XXXXX" << endl;

	  TH1F h_zdy("h_zdy", clean_name.Copy().Prepend("zdy "), nbins, bin_mins);
	  TH1F h_ll("h_ll", clean_name.Copy().Prepend("ll "), nbins, bin_mins);
	  TH1F h_qcd("h_qcd", clean_name.Copy().Prepend("QCD "), nbins, bin_mins);
	  TH1F h_zgj("h_zgj", clean_name.Copy().Prepend("zgj "), nbins, bin_mins);
	  for (vector<bin>::iterator it = bins.begin(); it != bins.end(); ++it)
	    {
	      int bin_num = it + 1 - bins.begin(); // +1 because 0 is underflow
	      h_zdy.SetBinContent(bin_num, (*it).zdy);
	      h_zdy.SetBinError(bin_num, (*it).zdyerr);
	      h_ll.SetBinContent(bin_num, (*it).ll);
	      h_ll.SetBinError(bin_num, (*it).llerr);
	      h_qcd.SetBinContent(bin_num, (*it).qcd);
	      h_qcd.SetBinError(bin_num, (*it).qcderr);
	      h_zgj.SetBinContent(bin_num, (*it).zgj);
	      h_zgj.SetBinError(bin_num, (*it).zgjerr);
	    }

	  TFile * outfile = TFile::Open(clean_name.Append(".root"), "RECREATE");
	  outfile->cd();
	  h_zdy.Write();
	  h_ll.Write();
	  h_qcd.Write();
	  h_zgj.Write();
	  outfile->Close();
	}
      else 
	{
	  cout << "could not open input file: " << i << ", " << inputFile << ". Exiting." << endl;
	  return 1;
	}
    }
}
