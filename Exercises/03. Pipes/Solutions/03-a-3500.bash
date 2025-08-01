#!/bin/bash



# 03-a-3500



cat /etc/passwd | cut -d ':' -f 5 | tr "[:lower:]" "[:upper:]"
