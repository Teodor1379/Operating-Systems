#!/bin/bash



# 03-a-5504



cat /etc/passwd | cut -d ':' -f 5 | cut -d ',' -f 1 | cut -d ' ' -f 2 | grep -v -E '.{8,}$' | sort | uniq | xargs -I{} grep -w {} /etc/passwd
