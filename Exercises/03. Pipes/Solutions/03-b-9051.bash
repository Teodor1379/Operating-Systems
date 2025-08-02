#!/bin/bash



# 03-b-9051



cat population.csv | grep -E ",2008," | sed -E 's/^(.)*,(2008,.*)/\1/g' | awk -F ',' 'BEGIN { sum = 0; } { sum = sum + $2; } END { print sum; }'
cat population.csv | grep -E ",2016," | sed -E 's/^(.)*,(2016,.*)/\1/g' | awk -F ',' 'BEGIN { sum = 0; } { sum = sum + $2; } END { print sum; }'
