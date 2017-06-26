// Merge GJ and DY tables

#include <iostream>
#include <fstream>
#include <cmath>

#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"

using namespace std;

int main (int argc, char ** argv)
{

  if (argc < 2) 
    {
      cout << "need input files" << endl;
      return 1;
    }

  for (int i = 1; i < argc; i++)
    {
      filebuf fbDY, fbGJ;
      char * inputFileDY = argv[i];
      TString in_name(inputFileDY);
      int last_slash = in_name.Last('/');
      int ss_length = (in_name.Length()) - last_slash;
      TString clean_name = in_name(last_slash+1, ss_length-1);
      cout << clean_name << endl;

      TString inputStringGJ = clean_name.Copy();
      inputStringGJ.Prepend("/home/users/dpg/MT2AnalysisEdit/MyCode/DataDrivenHistExtraction/tablesGJ/");
      const char * inputFileGJ = inputStringGJ.Data();

      ofstream outfile;
      outfile.open( clean_name.Data(), ios_base::app);
	  
      if (fbDY.open(inputFileDY,ios::in) && fbGJ.open(inputFileGJ,ios::in) )
	{
	  istream inputDY(&fbDY), inputGJ(&fbGJ);	  
	  TString contentsDY, contentsGJ;
	  contentsDY.ReadFile(inputDY);
	  contentsGJ.ReadFile(inputGJ);
	  TObjArray * tokensDY = contentsDY.Tokenize("\n\t ");
	  TObjArray * tokensGJ = contentsGJ.Tokenize("\n\t ");
	  for (int j = 0; j < tokensDY->GetEntries(); j++)
	    {
	      TString tokenj = ((TObjString *) (tokensDY->At(j)))->String();	      
	      TString tokenj1 = ((TObjString *) (tokensDY->At(j+1)))->String();	      
	      TString tokenj2 = ((TObjString *) (tokensDY->At(j+2)))->String();	      
	      if (tokenj.EqualTo("zinv"))
		{
		  outfile << "zinvDY\t" << tokenj1 << "\t" << tokenj2 << endl;
		  j+=2;
		}
	      else if (tokenj.EqualTo("bin"))
		{
		  outfile << "bin\t" << tokenj1 << endl;
		  j++;
		}
	      else if (tokenj.EqualTo("llep"))
		{
		  outfile << "llep\t" << tokenj1 << "\t" << tokenj2 << endl;
		  j+=2;
		}
	      else if (tokenj.EqualTo("qcd"))
		{
		  outfile << "qcd\t" << tokenj1 << "\t" << tokenj2 << endl;
		  TString tokenzgjrate = ((TObjString *) (tokensGJ->At(j-5)))->String();	      
		  TString tokenzgjerr = ((TObjString *) (tokensGJ->At(j-4)))->String();	      
		  outfile << "zinvGJ\t" << tokenzgjrate << "\t" << tokenzgjerr << endl;
		  j+=2;
		}
	    }
	  
	  fbDY.close();
	  tokensDY->Delete();
	  fbGJ.close();
	  tokensGJ->Delete();
	}
      else 
	{
	  cout << "could not open input files: " << i << ", " << inputFileDY << " or " << inputFileGJ << ". Exiting." << endl;
	  return 1;
	}
    }
}
