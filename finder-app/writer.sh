#!/bin/sh

if [ $# -ne 2 ]; then
    echo "Incorrect number of arguments"
    exit 1
fi

file=$1
content=$2

d=$(dirname "$file")

if [ ! -d "$d" ]; then
    mkdir -p $d
    echo "base is: $base"
    echo "file: $file"

    if [ ! -d "$d" ]; then
	echo "Failed to create directory"
	exit 1
    fi
fi

touch $file
if [ ! -w "$file" ] ; then
    printf 'cannot write to %s\n' "$file"
    exit 1
fi

echo $content > $file
