#!/bin/bash
cd $(cd "$(dirname "$0")" && pwd)
srcDIR=`pwd`

cd $srcDIR/build
cmake ..

make -j2
