#!/bin/bash



# 03-b-8600



find /usr -type f -name '*.sh' -exec head -n 1 {} \; | grep "^#!" | cut -c 3- | sort | uniq -c | sort -n -r | head -n 1 | awk ' { print $2; }'
