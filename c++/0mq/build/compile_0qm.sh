#!/bin/bash

echo "### Compile 0mq ###"

# Exit on any non-zero status.
trap 'exit' ERR
set -E

# Get variables based on the configuration
cd "$(dirname "$0")"
bash_dir=$(pwd)

# Compile libzmq
cd ../libs/0qm/libzmq
mkdir -p ./build
cd ./build
cmake ..
sudo make -j4 install

# Compile cppzmq
cd "$bash_dir"
cd ../libs/0qm/cppzmq
mkdir -p ./build
cd ./build
cmake ..
sudo make -j4 install

