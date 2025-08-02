#!/bin/bash



# 03-b-9054



cat population.csv | grep -E ",1969," | sed -E "^.*,(1969,.*)$/\1/g" | sort -n -t ',' -k 2 | head -n 42 | tail -n 1 | xargs -I{} grep -E "{}" population.csv | cut -d ',' -f 1,4
