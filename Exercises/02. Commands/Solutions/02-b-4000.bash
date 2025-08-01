#!/bin/bash



# 02-b-4000



cp "$(find /etc/ -type f -exec wc -c {} ';' 2> /dev/null | sort -n -k 1 | head -n 1 | cut -d ' ' -f 2-)" ~;
