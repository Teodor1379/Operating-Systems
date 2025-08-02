#!/bin/bash



# 03-b-9400



cat emp.data | awk '{ for (i = NF; i > 0; i -= 1) { printf $i"\t"} printf "\n"; }'
