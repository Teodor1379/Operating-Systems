#!/bin/bash



# 03-b-4005



cat ~/dir5/file1 | sed 's/[A-Z]/\L&/g' > ~/dir5/file2
