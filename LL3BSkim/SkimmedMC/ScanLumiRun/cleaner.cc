#include <iostream>
#include <fstream>
#include <boost/algorithm/string/classification.hpp> // is_any_of( ... )
#include <boost/algorithm/string/split.hpp> // split
#include <vector>
#include <string>

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

  while (! input.eof())
    {
      string nextline;
      getline(input, nextline);
      vector<string> split;
      boost::split(split, nextline, boost::is_any_of(" *\t"), boost::token_compress_on);
      if (split.size() < 5) continue;
      output << split.at(2) << ":" << split.at(3) << ":" << split.at(4) << endl;
    }

  input.close();
  output.close();
}
