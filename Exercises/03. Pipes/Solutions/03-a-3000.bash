#!/bin/bash



# 03-a-3000



df -P > dfOutFile;

cat dfOutFile | head -n -1 | sort -n -k 2;
