#!/bin/bash



# 03-b-9106



find ~/songs -type f -iname '*.ogg' -exec basename {} \; | sed -E 's/^(.*) - .*.ogg$/\1/g' | sort | uniq | tr -d ' ' | xargs -I{} mkdir -p ~/{}
