#!/bin/bash

echo "### Clean Boost system ###"

# Exit on any non-zero status.
trap 'exit' ERR
set -E

# Get variables based on the configuration
cd "$(dirname "$0")"
bash_dir=$(pwd)

rm -r */
