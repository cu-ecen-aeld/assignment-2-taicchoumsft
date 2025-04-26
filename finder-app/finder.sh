#!/bin/sh

if [ $# -ne 2 ]; then
   echo "Incorrect number of arguments supplied"
   exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d $filesdir ]; then
   echo "$filesdir does not exist"
   exit 1
fi

cnt_files=$(ls $filesdir | wc -l)
cnt_match=$(find $filesdir -type f | xargs grep -o $searchstr | wc -l)

echo "The number of files are $cnt_files and the number of matching lines are $cnt_match"
