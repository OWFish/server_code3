#!/bin/bash
#cd $(cd "$(dirname "$0")" && pwd)
#srcDIR=`pwd`
#cd gameworld/script/tolua++
#tolua++ -n server -o serverInterface.cc serverInterface.scp
mkdir GNU_Proj
cd GNU_Proj
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
#svn log -l 1 > web/server.version
