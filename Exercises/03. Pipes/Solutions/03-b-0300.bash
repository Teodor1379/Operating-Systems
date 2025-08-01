#!/bin/bash



# Solution 1 - ID

cat /etc/passwd | grep "$(id -u)" | cut -d ':' -f 4



# Solution 2 - Who am I

cat /etc/passwd | grep "^$(whoami)" | cut -d ':' -f 4
