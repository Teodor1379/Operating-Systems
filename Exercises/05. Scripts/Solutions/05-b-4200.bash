#!/bin/bash



# 05-b-4200



if [[ "${#}" -ne 1 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



if [[ ! -f "${1}" ]]; then
    echo "Argument 1 Error - Not a File!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Argument 1 Error - Not Redable!";

    exit 3;
fi



maxDepth=0
currentC=0


while read -r c; do
    if [[ "${c}" == "{" ]]; then
        currentC=$(( currentC + 1 ));
    else
        if [[ "${maxDepth}" -lt "${currentC}" ]]; then
            maxDepth="${currentC}";
        fi

        currentC=$(( currentC - 1 ));
    fi
done < <(cat "${1}" | grep -E -o '[{}]');



echo "The deepest nesting is ${maxDepth} levels deep.";
