#!/bin/bash



# 2023-SE-02



find /var/log/my_logs -type f -regex ".*/[a-zA-Z0-9_]+_[0-9]+\.log" -exec cat {} + 2> /dev/null | grep -o "error" | wc -l;
