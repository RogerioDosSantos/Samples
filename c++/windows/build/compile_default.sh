#!/bin/bash

echo "### Compile Platform Tester ###"

# Build configuration
config_project_name="platform_tester"
config_platform="default"
config_flavor="release"

# Exit on any non-zero status.
trap 'exit' ERR
set -E

echo " "
echo "*** Build Configuration:" 
echo "1 - Project Name: $config_project_name"
echo "2 - Platform: $config_platform"
echo "3 - Flavor: $config_flavor"

# Get variables based on the configuration
cd "$(dirname "$0")"
bash_dir=$(pwd)

build_dir="$bash_dir/$config_project_name"
mkdir -p $build_dir
cd $build_dir
build_dir="$(pwd)/$config_platform"
mkdir -p $build_dir
cd $build_dir
build_dir="$(pwd)/$config_flavor"
mkdir -p $build_dir
cd $build_dir
echo "A - Build Directory: $build_dir"

echo " "
echo "*** Staging:" 
cmake ../../../.. 

echo " "
echo "*** Compiling:" 
# make VERBOSE=1
make

echo "#############"


