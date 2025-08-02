#!/bin/bash



# 03-b-6100



cat /etc/passwd | head -n 46 | tail -n 18 | cut -d ':' -f 3 | rev | cut -c 1
