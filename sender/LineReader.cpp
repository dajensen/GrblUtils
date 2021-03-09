#include <iostream>
#include <fstream>
#include <string>
#include "LineReader.h"

using namespace std;

bool LineReader::ReadLine(std::string &out){
    bool rv = false;
    if(gcfile.is_open()) {
        if(getline(gcfile, out)){
            rv = true;
        }
    }
    return rv;
}

/*
int main () {
  string line;
  ifstream myfile ("example.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
*/