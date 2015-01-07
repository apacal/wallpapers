#!/bin/bash - 
#===============================================================================
#          FILE: shell_crontab.sh
#         USAGE: ./shell_crontab.sh 
#        AUTHOR: Apacal (), apacal@126.com
#       CREATED: 2015年01月07日 18:34
#      REVISION:  ---
#===============================================================================

sleep_time="30"
pid=`ps -ef | grep "shell_crontab.sh" | wc -l`
if [ $pid -gt 3 ]; then
    exit 1
fi
while [ "1" = "1" ];do
    /usr/bin/wallpapers now
    sleep $sleep_time
done

