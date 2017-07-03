// Read a datacard and output the bin, rate, and error for each background sample

#include <iostream>
#include <fstream>
#include <cmath>

#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"

#include "ReadCards.h"

using namespace std;

float GammaVariance (float k, float theta)
{
  return (k+1) * theta * theta;
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

	  float zinvrate = 0.0;
	  float lleprate = 0.0;
	  float qcdrate = 0.0;

	  float zlnN = 0.0;
	  float lllnN = 0.0;
	  float qcdlnN = 0.0;

	  float zgmN = 0.0;
	  float llgmN = 0.0;
	  float qcdgmN = 0.0;
	  
	  for (int j = 0; j < tokens->GetEntries(); j++)
	    {
	      TString tokenj = ((TObjString *) (tokens->At(j)))->String();	      
	      if (tokenj.EqualTo("zinv"))
		{
		  TString tokenZ = ((TObjString *) (tokens->At(j+10)))->String();	      
		  zinvrate = tokenZ.Atof();
		}
	      else if (tokenj.EqualTo("llep"))
		{
		  TString tokenll = ((TObjString *) (tokens->At(j+10)))->String();	      
		  lleprate = tokenll.Atof();
		}
	      else if (tokenj.EqualTo("qcd"))
		{
		  TString tokenQCD = ((TObjString *) (tokens->At(j+10)))->String();	      
		  qcdrate = tokenQCD.Atof();
		}
	      else if (tokenj.EqualTo("lnN"))
		{
		  TString tokenZ = ((TObjString *) (tokens->At(j+2)))->String();
		  TString tokenll = ((TObjString *) (tokens->At(j+3)))->String();
		  TString tokenQCD = ((TObjString *) (tokens->At(j+4)))->String();
		  if ( ! tokenZ.EqualTo("-") && ! tokenZ.Contains("nan") )
		    {
		      float minus1 = tokenZ.Atof() - 1;
		      zlnN += minus1 * minus1;
		    }
		  if ( ! tokenll.EqualTo("-") && ! tokenll.Contains("nan") )
		    {
		      float minus1 = tokenll.Atof() - 1;
		      lllnN += minus1 * minus1;		      
		    }
		  if ( ! tokenQCD.EqualTo("-") && ! tokenQCD.Contains("nan") )
		    {
		      float minus1 = tokenQCD.Atof() - 1;
		      qcdlnN += minus1 * minus1;
		    }
		}
	      else if (tokenj.EqualTo("gmN"))
		{
		  TString K = ((TObjString *) (tokens->At(j+1)))->String();
		  // j+2 is signal
		  TString Ztheta = ((TObjString *) (tokens->At(j+3)))->String();
		  TString lltheta = ((TObjString *) (tokens->At(j+4)))->String();
		  TString QCDtheta = ((TObjString *) (tokens->At(j+5)))->String();
		  if ( ! Ztheta.EqualTo("-") && ! Ztheta.Contains("nan"))
		    {
		      float zGamma = GammaVariance(K.Atof(), Ztheta.Atof());
		      zgmN += zGamma;
		    }
		  if ( ! lltheta.EqualTo("-") && ! lltheta.Contains("nan"))
		    {
		      float llGamma = GammaVariance(K.Atof(), lltheta.Atof());
		      llgmN += llGamma;		      
		    }
		  if ( ! QCDtheta.EqualTo("-") && ! QCDtheta.Contains("nan"))
		    {
		      float qcdGamma = GammaVariance(K.Atof(), QCDtheta.Atof());
		      qcdgmN += qcdGamma;
		    }
		}
	    }
	  float zerr = sqrt( (zlnN * zinvrate * zinvrate) + zgmN);
	  float llerr = sqrt( (lllnN * lleprate * lleprate) + llgmN);
	  float qcderr = sqrt( (qcdlnN * qcdrate * qcdrate) + qcdgmN);
	  
	  fb.close();
	  tokens->Delete();

	  // Now find the appropriate output file
	  // Form of file name is [header]/HTmintomax_jmintomax_bmintomax_m[t2]mintomax.txt
	  // we want a separate file for each HT-jet-b triple, but to print each mt2 bin in that file
	  TString in_name(inputFile);
	  int last_slash = in_name.Last('/');
	  int ss_length = (in_name.Length() - 4) - last_slash;
	  TString clean_name = in_name(last_slash+1, ss_length-1);
	  int last_underscore = clean_name.Last('_');
	  TString output_name = clean_name(0,last_underscore);
	  TString bin_name = clean_name(last_underscore + 1, clean_name.Length() - last_underscore);

	  ofstream outfile;
	  const char * prefix = in_name.Contains("withDY") ? "tablesDY/" : "tablesGJ/";
	  outfile.open( (output_name.Prepend(prefix)).Data(), ios_base::app);
	  outfile << "bin\t" << bin_name << endl;
	  outfile << "zinv\t" << zinvrate << "\t" << zerr << endl;
	  outfile << "llep\t" << lleprate << "\t" << llerr << endl;
	  outfile << "qcd\t" << qcdrate << "\t" << qcderr << endl;
	}
      else 
	{
	  cout << "could not open input file: " << i << ", " << inputFile << ". Exiting." << endl;
	  return 1;
	}
    }
}
