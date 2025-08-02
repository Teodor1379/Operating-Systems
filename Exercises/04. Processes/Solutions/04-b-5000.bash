#!/bin/bash



# 04-b-5000



ps -e -o egroup,rss | grep "^root" | awk 'BEGIN { sum = 0; } { sum = sum + $2; } END { print sum; }'
