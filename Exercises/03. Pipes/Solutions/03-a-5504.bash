#!/bin/bash



cat /etc/passwd | cut -d ':' -f 5 | cut -d ',' -f 1 | cut -d ' ' -f 2 | grep -v -E '.{8,}$' | sort | uniq | xargs -I{} grep -w {} /etc/passwd
