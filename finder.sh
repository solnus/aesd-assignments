#!/bin/bash

usage() {
    echo "[ $0 $1 $2 ]"
    echo "Usage: $0 [searchdir] [searchstring]"
    echo "Search for files in the target directory that contain the given string"
    echo
}

# Check that required args are given
if [ $# -ne 2 ]; then usage; exit 1; fi;

# Check that the specified directory exists
if [ ! -d $1 ]; then echo "Given directory does not exist. See usage."; exit 1; fi;

# Check that we have permissions to get a directory listing
if [ ! -r $1 ]; then echo "No read permissions on the given directory."; exit 1; fi;

files=$(find $1 -type f 2>/dev/null)
numfiles=$(echo "$files" | wc -l)
lines=$(echo "$files" | xargs grep $2 2>/dev/null | wc -l)

echo "The number of files are $numfiles and the number of matching lines are $lines"
