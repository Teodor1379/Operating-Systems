#!/bin/bash

# 2017-SE-01



find . -maxdepth 1 -type f -printf "%n %f\n" | sort -n -r | head -n 5 | cut -d' ' -f 2-
