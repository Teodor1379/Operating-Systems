#!/bin/bash



# 05-b-8000



if [[ "${#}" -ne 1 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



ps -e -o -user=,rss=,vsz=,pid=,tty= --sort=vsz | grep "^${1}" | awk '{ print $2 / $3; }';
