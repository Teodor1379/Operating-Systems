#!/bin/bash



# 03-b-9500



cat ssa-input.txt | awk 'BEGIN { array = ""; drive = ""; t1 = 0; t2 = 0; value = 0; }
    { if ($1 == "Array"         ) { array = $2; } }
    { if ($1 == "physicaldrive" ) { drive = $2; } }
    { if ($1 == "Current" && $2 == "Temperature") { t1 = $4;            } }
    { if ($1 == "Maximum" && $2 == "Temperature") { t2 = $4; value = 1; } }
    { if (value == 1) { printf "%s-%s %s %s\n", array, drive, t1, t2; value = 0; } }' | uniq
