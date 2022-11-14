#!/bin/bash
cd $(cd "$(dirname "$0")" && pwd)
path=`pwd`
echo "=============================================="
datetime=`date "+%Y-%m-%d.%H:%M:%S"`
echo $datetime" 正在启动数据服务..."
$path/bin/DBServer/dbserver > /dev/null
echo $datetime" 正在启动游戏服务..."
$path/bin/GameWorld/gameworld > /dev/null
echo $datetime" 正在启动网关服务..."
$path/bin/Gateway/gateway > /dev/null
echo $datetime" 正在启动日志服务..."
$path/bin/LoggerServer/loggerserver > /dev/null
#$path/Debug/gateway/gateway_ws_1219
nohup $path/serverdeamon.sh&
echo $datetime" 服务器启用完成!"
#svn log ./bin/gameworld/data/ -l 1 > web/script.version
