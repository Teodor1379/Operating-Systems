#!/bin/bash



# 03-b-8700



cat /etc/passwd | cut -d ':' -f 4 | sort -n | uniq -c | sort -n -r -k 1 | awk '{ print $2; }' | head -n 5 | xargs -I{} grep -w {} /etc/group | cut -d ':' -f 1
