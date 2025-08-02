#!/bin/bash



# 03-b-4003



cat ~/dir5/file1 | grep -o '.' | sort | uniq -c | sort -n | tail -n 1
cat ~/dir5/file2 | grep -o '.' | sort | uniq -c | sort -n | tail -n 1
cat ~/dir5/file3 | grep -o '.' | sort | uniq -c | sort -n | tail -n 1
