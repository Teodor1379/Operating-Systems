#!/bin/bash



# 03-b-8500



cat /etc/group | cut -d ':' -f 3 | awk -v mineID="$(id -g)" '{ if (mineID == $0) { print "Hello, $0 - I am here!"; } else { print "Hello, $0"; } }'
