#!/bin/bash



# 03-b-7500



cat /etc/services | grep -o "[A-Za-z]*" | tr "[:upper:]" "[:lower:]" | sort | uniq -c | sort -n -r | head
