#!/bin/bash



# 03-b-5300



cat /etc/passwd | cut -d ':' -f 5 | cut -d ',' -f 1 | grep -o "." | sort | uniq | wc -l
