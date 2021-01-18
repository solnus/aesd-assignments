#!/bin/bash

CROSSTOOL_VER=${CROSSTOOL_VER:=1.24.0}
BUILD_DIR=${BUILD_DIR:=$HOME/ctng_build_tmp}
BASE_BASE=${BUILD_BASE:=arm-unknown-linux-gnueabi}

echo "Building toolchain using crosstool-NG-$CROSSTOOL_VER into $BUILD_DIR with base $BUILD_BASE"

# Install prereqs
sudo apt install -y automake bison chrpath flex g++ gperf gawk libexpat1-dev libncurses5-dev libsdl1.2-dev libtool python2.7-dev texinfo help2man libtool-bin valgrind
if [[ $? -ne 0 ]]; then echo "Failed to install prerequisites"; echo 1; fi

# Prepare the build dir
if [[ -d $BUILD_DIR ]]; then rm -rdf $BUILD_DIR; fi
mkdir -p $BUILD_DIR

# Clone the source tree
cd $BUILD_DIR
git clone https://github.com/crosstool-ng/crosstool-ng.git
if [[ ! -d crosstool-ng ]]; then echo "Failed to clone crosstool-ng"; exit 1; fi
cd crosstool-ng

# Check out the desired version
git checkout crosstool-ng-$CROSSTOOL_VER
if [[ $? -ne 0 ]]; then echo "Failed to check out crosstool-ng-$CROSSTOOL_VER"; exit 1; fi

# Build/install locally
./bootstrap && ./configure --enable-local && make -j`nproc`
if [[ $? -ne 0 ]]; then echo "Failed to configure/make crosstool-ng"; exit 1; fi

# Run the tool
./ct-ng $BASE_BASE
./ct-ng menuconfig
./ct-ng build

# Clean up build dir
#rm -rdf $BUILD_DIR

