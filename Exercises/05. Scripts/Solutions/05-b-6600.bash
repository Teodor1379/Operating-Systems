#!/bin/bash



# 05-b-6600



if [[ "${#}" -ne 1 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



if [[ ! -d "${1}" ]]; then
    echo "Argument 1 Error - Not a Directory!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Argument 1 Error - Not Readable!";

    exit 3;
fi



while read -r file; do
    if [[ ! -e "${file}" ]]; then
        continue;
    fi

    while read -r another; do
        if [[ "${file}" == "${another}" ]]; then
            continue;
        fi

        diff -q "${file}" "${another}" > /dev/null;

        if [[ $? -eq 1 ]]; then
            if [[ "${file}" < "${another}" ]]; then
                rm "${another}";
            else
                rm "${file}";

                break;
            fi
        fi

    done < <(find "${1}" -mindepth 1 -maxdepth 1 -type f);
done < <(find "${1}" -mindepth 1 -maxdepth 1 -type f);
