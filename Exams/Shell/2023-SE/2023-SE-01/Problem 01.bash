#!/bin/bash



# 2023-SE-01



find / -type f -user "$(whoami)" -name "*.blend*" 2> /dev/null | grep -E "[0-9]+$"
