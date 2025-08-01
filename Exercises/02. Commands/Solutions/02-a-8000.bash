#!/bin/bash



# 02-a-8000



# Solution 1 - Chars

mkdir -p ~/myetc;

find /etc -perm -u+r,g+r,o+r -exec cp '{}' ~/myetc ';' 2> /dev/null;



# Solution 2 - Digits

mkdir -p ~/myetc;

find /etc -perm -444 -exec cp '{}' ~/myetc ';' 2> /dev/null;
