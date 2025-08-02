#!/bin/bash



# 03-b-9053



cat population.csv | grep -E ",2016," | sed -E 's/^.*,(2016,.*)$/\1/g' | cut -d ',' -f 2 | sort -n | head -n 1 | xargs -I{} grep -E ",2016,{}" population.csv | cut -d ',' -f 1
cat population.csv | grep -E ",2016," | sed -E 's/^.*,(2016,.*)$/\1/g' | cut -d ',' -f 2 | sort -n | head -n 1 | xargs -I{} grep -E ",2016,{}" population.csv | cut -d ',' -f 1
