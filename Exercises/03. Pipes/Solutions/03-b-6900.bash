#!/bin/bash



# 03-b-6900



find ~ -type f -printf "%T@ %p\n" | sort -n -r -k 1 -t ' ' | cut -d ' ' -f 2 | head -n 10
find ~ -type f -printf "%A@ %p\n" | sort -n -r -k 1 -t ' ' | cut -d ' ' -f 2 | head -n 10
