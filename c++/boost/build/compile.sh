#!/bin/bash

echo "### Compile boost_examples ###"

# Build configuration
config_project_name="examples"
config_platform="default"
config_flavor="release"
config_third_party_dir="/root/third-party"
config_stage_dir="../stage"

# Exit on any non-zero status.
trap 'exit' ERR
set -E

echo " "
echo "*** Bash Configuration:" 
echo "Project Name: $config_project_name"
echo "Platform: $config_platform"
echo "Flavor: $config_flavor"
echo "Third Party Directory: $config_third_party_dir"

# Get variables based on the configuration
cd "$(dirname "$0")"
bash_dir=$(pwd)

config_stage_dir="$bash_dir/$config_stage_dir"
mkdir -p $config_stage_dir
cd $config_stage_dir
config_stage_dir=$(pwd)
echo "Stage Directory: $config_stage_dir"

build_dir="$bash_dir/$config_project_name"
mkdir -p $build_dir
cd $build_dir
build_dir="$(pwd)/$config_platform"
mkdir -p $build_dir
cd $build_dir
build_dir="$(pwd)/$config_flavor"
mkdir -p $build_dir
cd $build_dir
echo "Build Directory: $build_dir"

echo " "
echo "*** Staging:" 
cmake ../../../.. -Dconfig_project_name="$config_project_name" -Dconfig_third_party_dir="$config_third_party_dir" -Dconfig_stage_dir="$config_stage_dir" -Dconfig_platform="$config_platform" -DCMAKE_BUILD_TYPE="$config_flavor"

echo " "
echo "*** Compiling:" 
# make VERBOSE=1
make

echo "#############"
