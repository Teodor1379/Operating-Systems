#!/bin/bash



# 2017-IN-01



find / -user "$(whoami)" 2> /dev/null | wc -l
