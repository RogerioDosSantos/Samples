#!/bin/bash

echo "### Compile Node Module ###"

# Go to the directory where the bash file is
cd "$(dirname "$0")"
echo "- Running from $(pwd)"

# Exit on any non-zero status.
trap 'exit' ERR
set -E

# Compile Node Module
node-gyp rebuild

# Create Output folder
mkdir -p ../stage
mkdir -p ../stage/node_modules
rm -f ../stage/node_modules/*.node
cp ./build/Release/*.node ../stage/node_modules

echo "#############"
