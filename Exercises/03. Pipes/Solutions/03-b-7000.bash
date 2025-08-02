#!/bin/bash



# 03-b-7000



find "/usr/include" -type f -name "*.[ch]" | wc -l 2> /dev/null

find "/usr/include" -type f -name "*.[ch]" -exec cat {} \; | wc -l 2> /dev/null
