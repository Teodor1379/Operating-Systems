#!/bin/bash



# 05-b-4400



if [[ "${#}" -gt 2 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



directory1="${1}";
directory2="${2}";

if [[ "${directory2}" == "" ]]; then
    directory2=$(date -I);

    mkdir -p "${directory2}";
fi



if [[ ! -d "${directory1}" ]]; then echo "Argument 1 Error - Not a Directory!"; exit 2; fi
if [[ ! -d "${directory2}" ]]; then echo "Argument 2 Error - Not a Directory!"; exit 2; fi

if [[ ! -r "${directory1}"  ]]; then echo "Argument 1 Error - Not readable!";   exit 3; fi
if [[ ! -w "${directory2}"  ]]; then echo "Argument 2 Error - Not writable!";   exit 3; fi



while read -r line; do
    cp "${line}" "${directory2}/${line}";
done < <(find "${directory1}" -type f -mmin -45);



tar -c -f "${directory2}.tar" "${directory2}";
