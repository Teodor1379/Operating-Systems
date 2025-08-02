#!/bin/bash



# 03-b-6700



find /tmp -type f -readable -printf "%m %f\n" 2> /dev/null
