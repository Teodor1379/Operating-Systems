#!/bin/bash

# 2018-SE-02



find $(getent passwd pesho | cut -d ':' -f 6) -type f -links +1 -printf "%T@ %i\n" 2> /dev/null | sort -n -r | head -n 1 | cut -d ' ' -f 2
