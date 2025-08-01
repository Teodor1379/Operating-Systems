#!/bin/bash



# 02-a-0601



mkdir -p ~/practice/01

touch ~/practice/01/f{1,2,3}

mkdir -p ~/dir1

cp ~/practice/01/f{1,2,3} ~/dir1/

mkdir -p ~/dir2

mv ~/dir1/f2 ~/dir2/numbers
