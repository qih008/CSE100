/*
 * Name: Qing Huang <qih008>
 * Project: PA2
 * Date: 7/16/2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 3)                        // check incorrect arguments
  {
    cerr << "Incorrect arguments number! " << endl;
    return -1;
  }
  if((string)argv[1] == (string)argv[2])  // check same name
  {
    cerr << "infile and outfile must be different files " << endl;
    return -1;
  }

  ifstream input;
  ofstream output;
  input.open(argv[1]);                 // open compressed file
  if(!input.good())
  {
    cerr << "Couldn't open " << argv[1] << endl;
    return -1;
  }
  else cout << "Reading header from file " << argv[1] << "...";

  vector<int> freq(256, 0);
  int total = 0;
  int kind = 0;
  string symb;

  for(int i=0; i<256; i++)   // read header for first 256 lines
  {
    getline(input, symb);    // get header info from each line in string
    freq[i] = atoi(symb.c_str());      // change string to int
    total = total + freq[i];           // add frequence of per char to total
  }
  for(int i=0; i<freq.size(); i++)     // find how many symbols
  {
    if(freq[i] != 0)
      kind++;                          // symbols number +1
  }
  cout << " done. " << endl;           // done for read header
  cout << "Uncompressed file will have " <<kind<<" unique symbols and size ";
  cout << total << " bytes." << endl;

  cout << "Building Huffman code tree...";
  HCTree hcTree;                       // reconstruct hc tree
  hcTree.build(freq);
  cout << " done." << endl;

  output.open(argv[2]);                // open decode output file
  if(!output.good())
  {
    cerr << "Couldn't open " << argv[2] << endl;
    return -1;
  }
  else cout << "Writing to file " << argv[2] << "...";
  
  BitInputStream* is = new BitInputStream(input);
  for(int i=0; i<total; i++)           // decode the compressed file
    output << (unsigned char)hcTree.decode(*is); // call decode funtion
  cout << " done." << endl;

  input.close();
  output.close();
  cout << "Finish Uncompressing " << endl;
  return 0;
}

