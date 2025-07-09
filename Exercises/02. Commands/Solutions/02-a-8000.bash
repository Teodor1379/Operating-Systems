#!/bin/bash



mkdir -p ~/myetc

find /etc -perm 444 -exec cp {} ~/myetc \;
