#!/bin/bash



# 04-b-8000



ps -e -o pid=,tty=,cmd= | awk '{ if ($2 == "?") { print $1"\t"$3; } }' | sort -k 2 -u
