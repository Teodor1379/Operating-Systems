#!/bin/bash



# 04-a-6000



ps -e --sort=vsz -o pid=,cmd= | tail -n 1
