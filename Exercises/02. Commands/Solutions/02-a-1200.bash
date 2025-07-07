#!/bin/bash



# Solution 1 - Full Names

find /home -type d 2> /dev/null



# Solution 2 - Single Names

find /home -type d -exec basename {} \; 2> /dev/null
