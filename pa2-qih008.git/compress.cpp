/*
 * Name: Qing Huang <qih008>
 * Project: PA2
 * Date: 7/15/2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 3)      // check incorrect arguments
  {
    cerr << " Incorrect arguments number! " << endl;
    return -1;
  }
  if((string)argv[1] == (string)argv[2])  // check input and output filename
  {
    cerr << "infile and outfile must be different files " << endl;
    return -1;
  }

  ifstream input;
  ofstream output;
  vector<int> freq(256, 0);    // vector for build tree
  byte symb;                   // temp symbol
  int total = 0;               // sizeof total characters are passed
  int kind = 0;                // sizeof different kind characters are passed
                               // 1st read file, trying to find freq of char
  input.open(argv[1]);         // open input file
  if(!input.good())            // check if open correct or not
  {
    cerr << " Couldn't open " << argv[1] << endl;
    return -1;
  }
  else cout << "Reading from file " << argv[1] << "...";

  while(input.good())          // counting data
  {
    symb = input.get();        // last get is newline
    if(input.eof()) break;     // break if end of file
    freq[(int)symb]++;         // frenquence of above char
    total++;                   // total count +1
  }
  for(int i=0; i<freq.size(); i++) 
  {                            // find how many kind of symbols
    if(freq[i])
      kind++;
  }
  cout << " done. " << endl;
  cout <<"Found " << kind << " unique symbols in input file of size ";
  cout << total << " bytes." << endl;
  input.close();

  cout << "Building Huffman code tree...";
  HCTree hcTree;
  hcTree.build(freq);          // call build method to build tree
  cout << " done." << endl; 
                               // reading to insert header and encode
  output.open(argv[2]);        // open output file
  if(!output.good())
  {
    cerr << " Couldn't open " << argv[2] << endl;
    return -1;
  }
  else cout << "Writing to file " << argv[2] << "...";
 
  BitOutputStream* os = new BitOutputStream(output);
  for(int i=0; i<freq.size(); i++)  // insert header to outFile
    output << freq[i] << endl;      // header for 256 lines

  input.open(argv[1]);           // 2nd readfile to encoding
  while(input.good())            // begin encode
  {
    symb = input.get();          // read again
    if(input.eof()) break;       // exit if end of file
    hcTree.encode(symb, *os);    // use hc code to encode those symbol
  }
  os->flush();                   // flush the last uncomplete buf
  cout << " done." << endl;
  size_t outByte = output.tellp(); // find size of output file
  cout << "Output file has size " << outByte << " bytes." << endl;
  input.close();
  output.close();
  cout << "Finish Compressing!!! " << endl;
  return 0;
}

