#!/bin/bash



# 03-b-9052



cat population.csv | grep -E "^Bulgaria,*" | sort -n -r -t ',' -k 4 | head -n 1 | cut -d ',' -f 3
