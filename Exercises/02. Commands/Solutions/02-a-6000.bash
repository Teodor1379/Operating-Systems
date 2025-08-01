#!/bin/bash



# 02-a-6000



# Solution 1 - Chars

find /bin -type f -perm -a=rwx 2> /dev/null



# Solution 2 - Digits

find /bin -type f -perm 777 2> /dev/null
