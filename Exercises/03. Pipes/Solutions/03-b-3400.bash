#!/bin/bash



# Solution 1 - Part-Line Comments

cat /etc/services | grep "#" | wc -l;



# Solution 2 - Full-Line Comments

cat /etc/services | grep "^#" | wc -l;
