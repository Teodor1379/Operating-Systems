#!/bin/bash



# 05-b-7200



for file in "${@}"; do
    if [[ -f "${file}" ]]; then
        if [[ -r "${file}" ]]; then
            echo "The file ${file} is readable!";
        else
            echo "The file ${file} is not readable!";
        fi
    elif [[ -d "${file}" ]]; then
        entries=$(find "${file}" -mindepth 1 -type f 2> /dev/null | wc -l);

        while read -r current; do
            if [[ "${entries}" -gt $(stat -c "%s" "${current}") ]]; then
                echo "${current}";
            fi
        done < <(find "${file}" -mindepth 1 -type f 2> /dev/null);
    fi
done
