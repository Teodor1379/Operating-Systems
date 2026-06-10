#!/bin/bash



# 2017-IN-03



cat /etc/passwd | grep "/home/Inf" | cut -d ':' -f 1,5 | cut -d ',' -f 1 | \
    grep -E 'a$' | cut -d ':' -f 1 | cut -c 3,4 | sort -n | uniq -c | sort -n -r | head -n 1
