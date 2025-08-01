#!/bin/bash



# 02-a-5504



find /tmp -type f -gid "$(id -g)" -perms -g=w,o=w 2> /dev/null
