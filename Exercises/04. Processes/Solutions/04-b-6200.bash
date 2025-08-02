#!/bin/bash



# 04-b-6200



ps -e -o user= | grep -F -v -f <(who | cut -d ' ' -f 1 | sort -u) | sort | uniq
