#!/bin/bash
cd $(cd "$(dirname "$0")" && pwd)
mysql -uroot -p1234 -e"insert into actor_h10ll.gmcmd(serverid,cmd) values(10,'rsf')"
svn log ./Debug/gameworld/data/ -l 1 > web/script.version
