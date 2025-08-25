#!/bin/bash



# 05-b-9100



if [[ "${#}" -ne 2 ]]; then
    echo "Expected Different Arguments";

    exit 1;
fi



if [[ ! -d "${1}" ]]; then echo "Argument 1 Error - Not a Directory!";  exit 2; fi
if [[ ! -d "${2}" ]]; then echo "Argument 2 Error - Not a Directory!";  exit 2; fi

if [[ ! -r "${1}" ]]; then echo "Argument 1 Error - Not Readable!"; exit 3; fi
if [[ ! -w "${2}" ]]; then echo "Argument 2 Error - Not Writable!"; exit 3; fi



extensions=$(find "${SOURCE}" -type f 2> /dev/null | sed "s/^.*\.(.*)$/\1/g" | sort | uniq);




for extension in $extensions; do
    mkdir "${DESTINATION}/${extension}";
done



while read -r file; do
    extension="$(echo "${file}" | sed "s/^.*\.(.*)$/\1/g")";

    mv "${file}" "${DESTINATION}/${extension}/${file}";
done < <(find "${SOURCE}" -type f 2> /dev/null);
