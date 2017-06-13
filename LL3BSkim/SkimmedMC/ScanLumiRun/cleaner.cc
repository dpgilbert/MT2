#include <iostream>
#include <fstream>
#include <boost/algorithm/string/classification.hpp> // is_any_of( ... )
#include <boost/algorithm/string/split.hpp> // split


using namespace std;

int main (int argc, char ** argv)
{  
  if (argc != 3)
    {
      cout << "Usage: ./cleaner.exe input_file output_file";
      return 1;
    }

  ifstream input(argv[1]);
  if (!input) 
    {
      cout << "problem with input" << endl;
      return 1;
    }
  ofstream output(argv[2]);

  int n;
  int counter = 0;
  while (!input.eof() && counter < 3)
    {      
      if (n == 42) // asterisk 
	continue;
      cout << n;
      if (! input >> n) continue;
      if (counter == 0)
	{
	  counter++;
	}
      else if (counter < 3)
	{
	  counter++;
	  output << n << ":";
	}
      else if (counter == 3)
	{
	  counter = 0;
	  output << n << endl;
	}
    }

  input.close();
  output.close();
}
