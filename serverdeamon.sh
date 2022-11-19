#while (true)
#do
#
# ret=`ps aux |grep gameworld|grep -v grep|grep -v "/bin/bash"|awk '{print $11}'`
# if ((${#ret} == 0))
# then
#	 `pwd`/Debug/gameworld
# fi
# ret=`ps aux |grep dbserver|grep -v grep|grep -v "/bin/bash"|awk '{print $11}'`
# if ((${#ret} == 0))
# then
#	 `pwd`/Debug/dbserver
# fi
# echo 'hehe'
# sleep 5
# done


while true;
do
	ret=`ps x |grep gameworld|grep -v grep|grep -v "/bin/bash"|wc -l`
	if [ $ret == 0 ];
	then
		`pwd`/bin/GameWorld/gameworld
	fi
	ret=`ps x |grep dbserver|grep -v grep|grep -v "/bin/bash"|wc -l`
	if [ $ret == 0 ];
	then
		`pwd`/bin/DBServer/dbserver
	fi
	sleep 10
done

