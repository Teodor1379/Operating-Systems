#!/bin/bash



# 03-b-9105



find ~/songs -type f -iname '*.ogg' -exec basename {} \; | sed -E 's/^(.*) - (.*) \(.*\).ogg$/\1 - \2/g' | grep -E -w "^(Beatles|Pink) - " | cut -d '-' -f 2- | cut -c 2- | wc -l
find ~/songs -type f -iname '*.ogg' -exec basename {} \; | sed -E 's/^(.*) - (.*) \(.*\).ogg$/\1 - \2/g' | grep -E -w "^(Beatles|Pink) - " | cut -d '-' -f 2- | cut -c 2-
