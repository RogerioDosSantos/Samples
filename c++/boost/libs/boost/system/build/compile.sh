#!/bin/bash

echo "### Compile Boost system ###"

# Build configuration
config_project_name="$1"
config_platform="$2"
config_flavor="$3"
config_third_party_dir="$4"
config_stage_dir="$5"

# Exit on any non-zero status.
trap 'exit' ERR
set -E

echo " "
echo "*** Configuration:" 
echo "1 - Project Name: $config_project_name"
echo "2 - Platform: $config_platform"
echo "3 - Flavor: $config_flavor"
echo "4 - Third Party Directory: $config_third_party_dir"
echo "5 - Stage Directory: $config_stage_dir"

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
echo " - Build Directory: $build_dir"

echo " "
echo "*** Staging:" 
cmake ../../../.. -Dconfig_project_name="$config_project_name" -Dconfig_third_party_dir="$config_third_party_dir" -Dconfig_stage_dir="$config_stage_dir" -Dconfig_platform="$config_platform" -DCMAKE_BUILD_TYPE="$config_flavor"

echo " "
echo "*** Compiling:" 
# make VERBOSE=1
make

echo "#############"
