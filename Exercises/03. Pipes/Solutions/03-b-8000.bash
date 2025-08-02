#!/bin/bash



# 03-b-8000



cat mypasswd.txt | grep "/home/SI" | cut -d ':' -f 1 | cut -c 2- | grep -v "[a-zA-Z]" | sort -n -r > si.txt
