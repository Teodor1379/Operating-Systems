#!/bin/bash



# 03-b-3600



find / -mindepth 1 -maxdepth 3 -type d > /dev/null 2> dirs.txt

cat dirs.txt | cut -d ':' -f 2 | tr -d ' ' | cut -c 4- | rev | cut -c 4- | rev;

rm dirs.txt
