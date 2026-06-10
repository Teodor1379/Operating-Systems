#!/bin/bash



# 2017-IN-02



find . -mindepth 1 -maxdepth 2 -type f -size 0 -exec rm -i {} \; 2> /dev/null



find ~ -mindepth 1 -maxdepth 2 -type f -user "$(whoami)" -printf "%p %s" 2> /dev/null \
    | sort -n -t ' ' -k 2 | tail -n 5 | cut -d ' ' -f 1 | xargs -r rm -i 
