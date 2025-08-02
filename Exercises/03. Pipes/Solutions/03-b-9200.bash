#!/bin/bash



# 03-b-9200



find . -type f,d -printf "%m %p\n" -perm "$(find /etc -type f -printf "%s %m\n" 2> /dev/null | sort -n | tail -n 1 | cut -d ' ' -f 2)" 2> /dev/null
