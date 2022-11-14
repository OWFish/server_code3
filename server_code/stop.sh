#!/bin/bash
cd $(cd "$(dirname "$0")" && pwd)

key1=`pwd`
datetime=`date "+%Y-%m-%d.%H:%M:%S"`

key2="serverdeamon.sh"
ps aux |grep $key1|grep $key2|grep -v grep|awk '{print $2}'|xargs kill -15
ret=`ps aux |grep $key1|grep $key2|grep -v grep|awk '{print $11}'`
echo "kill "$key1" "$key2" "$ret

key2="gateway"
ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $2}'|xargs kill -15
ret=`ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $11}'`
echo "kill "$key1" "$key2" "$ret

key2="gameworld"
ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $2}'|xargs kill -15
ret=`ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $11}'`
echo $datetime" 开始结束游戏服务 "$key1" "$key2" "$ret
while true; do
	datetime=`date "+%Y-%m-%d.%H:%M:%S"`
	proc=`ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|wc -l`
	if [ $proc == 0 ];
	then
		break
	fi
	echo $datetime" 游戏服务 "$key1" "$key2" 结束中..."
	sleep 1
done
echo $datetime" 游戏服务 "$key1" "$key2" 停止完成!"

key2="dbserver"
ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $2}'|xargs kill -15
ret=`ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $11}'`
echo $datetime" 开始结束数据服务 "$key1" "$key2" "$ret
while true; do
	datetime=`date "+%Y-%m-%d.%H:%M:%S"`
	proc=`ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|wc -l`
    if [ $proc == 0 ];
    then
        break
    fi
	echo $datetime" 数据服务 "$key1" "$key2" 保存数据中..."
    sleep 1
done
datetime=`date "+%Y-%m-%d.%H:%M:%S"`
echo $datetime" 数据服务 "$key1" "$key2" 停止完成!"

key2="loggerserver"
ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $2}'|xargs kill -9
ret=`ps aux |grep $key1|grep $key2|grep -v grep|grep -v "/bin/bash"|awk '{print $11}'`
echo "kill "$key1" "$key2" "$ret
