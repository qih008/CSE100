#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: $0 <num_chars_in_outfile> <outfile>"
        exit 1;
	fi

	symbols="a b c d e f"

	for i in $( seq 1 $1 )
	do
	    c=`shuf -e $symbols -n 1`
	        printf "%s" $c >> $2
		done
