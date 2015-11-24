#!/bin/sh

deluged
echo "deluged" | atq 22:30
echo "killall deluged && sudo rtcwake -t `date -d "today 22:00:00" +%s` -m disk"| atq 11:00

