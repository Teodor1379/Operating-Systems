#!/bin/bash



# 03-b-9103



find ~/songs -type f -iname '*.ogg' -exec basename {} \; | sed -E 's/^(.*) - (.*) \((.*), (.*)\).ogg$/\2/g' | tr ' ' '_' | tr "[:upper:]" "[:lower:]" | sort
