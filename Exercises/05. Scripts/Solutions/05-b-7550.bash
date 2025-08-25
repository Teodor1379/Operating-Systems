#!/bin/bash



# 05-b-7550



if [[ "${#}" -ne 1 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



index=0;

while read -r line; do
    prc=$(echo "${line}" | awk '{ print $1; }');
    pid=$(echo "${line}" | awk '{ print $2; }');

    index=$(( index + 1 ));

    kill "${pid}";
done < <(ps -e -o user=,pid= | grep "^{1}");



echo "Stopped processes: ${index}.";
