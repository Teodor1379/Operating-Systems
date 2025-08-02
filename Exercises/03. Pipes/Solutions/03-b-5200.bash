#!/bin/bash



# 03-b-5200



cat /etc/passwd | grep -o "." | grep -v "а" | wc -l
