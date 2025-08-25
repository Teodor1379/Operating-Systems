#!/bin/bash



# 05-b-6800



if [[ "${#}" -gt 2 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



dir="${1}";
par="${2}";



if [[ ! -d "${dir}" ]]; then
    echo "Argument 1 Error - Not a Directory!";

    exit 2;
fi

if [[ ! -r "${dir}" ]]; then
    echo "Argument 1 Error - Not Readable!";

    exit 2;
fi



if [[ "${par}" != "" && "${par}" != "-a" ]]; then
    echo "Argument 2 Error - Invalid Argument!";

    exit 3;
fi



while read -r entry; do
    if [[ -f "${entry}" ]]; then
        echo "${entry} ($(stat -c "%s" ${entry}) bytes)";
    elif [[ -d "${entry}" ]]; then
        echo "${entry} ($(find ${entry} -maxdepth 1| wc -l) entries)";
    fi
done < <(find "${dir}" -maxdepth 1 -exec basename {} \;);
