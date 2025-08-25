#!/bin/bash



# 05-b-7700



if [[ "${#}" -ne 2 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



if [[ ! -d "${1}" ]]; then
    echo "Argument 1 Error - Not a Directory!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Argument 1 Error - Not Readable!";

    exit 2;
fi



if [[ ! "${2}" =~ ^[1-9]{1}[0-9]*$ && ! "${2}" =~ ^0$ ]]; then
    echo "Argument 2 Error - Not a Number!";

    exit 3;
fi




sum=0;

while read -r fileS; do
    sum=$(( sum + fileS ));
done < <(find "${1}" -type f -size +"${2}c" -printf "%s\n");



echo "The sum is: ${sum}.";
