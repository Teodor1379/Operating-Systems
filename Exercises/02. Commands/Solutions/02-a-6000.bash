#!/bin/bash



# Solution 1 - Chars

find /bin -type f -perm -a=rwx 2> /dev/null



# Solution 2 - Digits

find /bin -type f -perm 777 2> /dev/null
