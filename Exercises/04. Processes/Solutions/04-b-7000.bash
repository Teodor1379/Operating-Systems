#!/bin/bash



# 04-b-7000



ps -e -o egroup,drs= | grep "^root" | awk 'BEGIN { s = 0; c = 0; } { s = s + $2; c = c + 1; } END { if (c > 0) { print s / c; } else { print 0; } }'
