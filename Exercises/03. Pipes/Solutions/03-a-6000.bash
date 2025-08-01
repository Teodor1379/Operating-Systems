#!/bin/bash



# 03-a-6000



cat emp.data | awk 'END { print NR; }'

cat emp.data | awk '{ if (NR == 3) { print $0; } }'

cat emp.data | awk '{ print $NF; }'

cat emp.data | awk 'END { print $NF; }'

cat emp.data | awk '{ if (NF > 4) { print $0; } }'

cat emp.data | awk '{ if ($NF > 4) { print $0; } }'

cat emp.data | awk '{ print NF; }'

cat emp.data | awk 'BEGIN { i = 0; } { if (/.*Beth.*/) { i = i + 1; } } END { print i; }'

cat emp.data | awk 'BEGIN { max = 0; row = ""; } { if (max < $3) { max = $3; row = $0; } } { END print max" "row"\n"; }'

cat emp.data | awk '{ if (NR > 0) { print $0; } }'

cat emp.data | awk '{ if (length($0) > 17) { print $0; } }'

cat emp.data | awk '{ print NF, $0; }'

cat emp.data | awk '{ print $2, $1; }'

cat emp.data | awk 'BEGIN { temp = ""; } { temp = $1; $1 = $2; $2 = temp; print $0; }'

cat emp.data | awk '{ $1 = $NR; print $0; }'

cat emp.data | awk '{ $2 = ""; print $0; }'

cat emp.data | awk '{ printf "%.2f\n", $2 + $3; }'

cat emp.data | awk 'BEGIN { sum = 0; } { sum = sum + $2 + $3; } END { print sum; }'
