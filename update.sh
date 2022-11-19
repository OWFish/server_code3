#!/bin/bash
cd $(cd "$(dirname "$0")" && pwd)
cur=`pwd`
svn up
cd Debug/gameworld/data
svn up
#cd $cur/Debug/loggerserver/data
#svn up
