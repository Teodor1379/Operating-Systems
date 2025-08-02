#!/bin/bash



# 04-b-9000



ps -e -o pid=,ppid= | awk '{ parent[$1] = $2; children[$2] += 1; }
    END { for (child in children) { if (children[child] > children[parent[child]]) } { print child; } }'
