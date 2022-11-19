#!/bin/bash
cd $(cd "$(dirname "$0")" && pwd)
datetime=`date "+%Y-%m-%d.%H:%M:%S"`
echo $datetime" 开始打包..."
currentDir=`pwd`

# 版本号
version=`date "+%Y-%m-%d"`
echo "version:"$version
tarVerFile="server_"$version".tar.gz"
tarFile="server.tar.gz"
cd $currentDir

# 创建打包目录
mkdir history_pack
mkdir pack
mkdir pack/Debug
mkdir pack/Debug/gameworld
mkdir pack/Debug/dbserver
mkdir pack/Debug/loggerserver
mkdir pack/Debug/gateway
mkdir pack/sql

# 拷贝可执行文件
echo "cp gameworld"
cp  bin/GameWorld/gameworld pack/Debug/gameworld/gameworld
echo "cp dbserver"
cp  bin/DBServer/dbserver pack/Debug/dbserver/dbserver
echo "cp loggerserver"
cp  bin/LoggerServer/loggerserver pack/Debug/loggerserver/loggerserver
echo "cp gateway"
cp	bin/Gateway/gateway pack/Debug/gateway/gateway

echo "cp sql"
cp	sql/*.sql pack/sql
echo "rsync gameworld_data"
rsync -a -r --exclude .svn/ bin/GameWorld/data/functions/* pack/functions/


# 压缩
cd pack
echo "tar to "$tarFile
tar -czf $tarFile *
mv $tarFile ../
cd ..
echo $tarFile
echo "backup this version packet:"$tarVerFile
cp $tarFile ./history_pack/$tarVerFile

# 后续处理
echo "打包完成!"