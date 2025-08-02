#!/bin/bash



# 03-b-9300



cat emails.txt | grep -E '^[a-zA-Z0-9_][a-zA-Z0-9_.-]*[a-zA-Z0-9_]@[a-zA-Z0-9][a-zA-Z0-9_.-]*.[a-zA-Z]*$' | grep -v '.*[.][.].*'
