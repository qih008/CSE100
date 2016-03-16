/*
 * Name: Qing Huang <qih008>
 * Project: PA2
 * Date: 7/16/2014
 */

#include "BitInputStream.hpp"

void BitInputStream::fill()
{
  buf = in.get();  // get new char when old is all read
  bufi = 0;        // reset to 0 index
}

int BitInputStream::readBit()
{
  if(bufi == 8)    // check read all buf
    fill();        // fill new buf
    
  int bit = (1&buf>>bufi); // read from lsb to msb
  bufi++;
  return bit;
}
