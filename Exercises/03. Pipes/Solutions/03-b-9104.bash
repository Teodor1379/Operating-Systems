#!/bin/bash



# 03-b-9104



find ~/songs -type f -iname '*.ogg' -exec basename {} \; | sed -E 's/^(.*) - (.*) \((.*), (.*)\)$/\3,\4/g' | sort -n -t ',' -k 2
