#!/bin/bash



# Solution 1 - Multiple Arguments

mkdir -p ~/practice/01

cd ~/practice/01 || exit

touch f1 f2 f3

mkdir -p ~/dir1

cp f1 ~/dir1
cp f2 ~/dir2
cp f3 ~/dir3



# Solution 2 - Single Argument

mkdir -p ~/practice/01

touch ~/practice/01/f{1,2,3}

mkdir -p ~/dir1

cp ~/practice/01/f{1,2,3} ~/dir1/
