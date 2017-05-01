#!/bin/bash

echo "### Compile Boost chrono ###"

# Build configuration
config_project_name="boost"
config_platform="default"
config_flavor="release"
config_third_party_dir="/root/third-party"
config_stage_dir="../../../../stage"

# Get variables based on the configuration
cd "$(dirname "$0")"
bash_dir=$(pwd)

# Exit on any non-zero status.
trap 'exit' ERR
set -E

config_stage_dir="$bash_dir/$config_stage_dir"
mkdir -p $config_stage_dir
cd $config_stage_dir
config_stage_dir=$(pwd)

$bash_dir/compile.sh "$config_project_name" "$config_platform" "$config_flavor" "$config_third_party_dir" "$config_stage_dir"
