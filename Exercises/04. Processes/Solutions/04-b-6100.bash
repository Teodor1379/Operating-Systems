#!/bin/bash



# 04-b-6100



ps -e -o user=,cmd= | grep "vim" | awk '{ print $1; }' | sort | uniq -c | awk '{ if ($1 > 1) { print $2; } }'
