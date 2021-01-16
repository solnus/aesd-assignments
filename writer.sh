#!/bin/bash

usage() {
    echo "Usage: $0 [writefile] [writestring]"
    echo "Writes the given string to the given file, overwriting if it exists."
    echo
}

# Check that required args are given
if [ $# -ne 2 ]; then usage; exit 1; fi;

# Check if the argument is a directory
if [[ -d $1 || $1 =~ ".*/" ]]; then echo "Argument is a directory; must be a filename."; exit 1; fi;

# Try to create the directory tree for the file if necessary
if [[ ! -d $(dirname $1) && (-f $(dirname $1) || $(mkdir -p $(dirname $1)) -ne 0) ]]; then
  echo "Failed to create directory tree for file.";
  exit 1;
fi

# Try to create the file if necessary
if [[ ! -f $1 && $(echo 2 > $1) -ne 0 ]]; then
  echo "Failed to create file.";
  exit 1;
fi

echo $2 > $1