#!/bin/bash



find / -type f -user "$(whoami)" -name "*.blend*" 2> /dev/null | grep -E "[0-9]+$"
