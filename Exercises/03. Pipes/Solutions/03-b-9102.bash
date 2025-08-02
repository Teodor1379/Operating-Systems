#!/bin/bash



# 03-b-9102



find ~ -type f -iname '*.ogg' -exec basename {} ';' | sed -E 's/^(.*) - (.*) \((.*), (.*)\).ogg$/\2/g'
