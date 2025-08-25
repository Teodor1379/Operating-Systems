#!/bin/bash



# 05-b-4800



if [[ "${#}" -ne 2 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



if [[ ! -f "${1}" ]]; then echo "Argument 1 Error - Not a File!"    ;   exit 2; fi
if [[ ! -d "${2}" ]]; then echo "Argument 2 Error - Not a Directory";   exit 2; fi



if [[ ! -r "${1}" ]]; then echo "Argument 1 Error - Not Readable!"  ;   exit 3; fi
if [[ ! -r "${2}" ]]; then echo "Argument 2 Error - Not Readable!"  ;   exit 3; fi



while read -r file; do
    diff -q "${file}" "${1}" > /dev/null

    if [[ ${?} -eq 0 ]]; then
        echo "${file}";
    fi    
done < <(find "${2}" -type f 2> /dev/null);
