/*
 * Name: Qing Huang <qih008>
 * Project: PA2
 * Date: 7/16/2014
 */

#include "BitOutputStream.hpp"

void BitOutputStream::flush()
{
  out.put(buf);         // send buf to output
  out.flush();
  buf = bufi = 0;       // clear it to 0
}

void BitOutputStream::writeBit(int bit)
{
  if(bufi == 8)          // check buf is full
    flush();             // if full, output buf
    
                         // store from lsb to msb
  buf = buf | (bit<<bufi);    // use or to store bit in buf
  bufi++;                // buf index +1
}
