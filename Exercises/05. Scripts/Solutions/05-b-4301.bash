#!/bin/bash



# 05-b-4301



if [[ "${#}" -ne 3 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



if [[ ! -f "${1}" ]]; then echo "Argument 1 Error - Not a File  !"; exit 2; fi
if [[ ! -d "${1}" ]]; then echo "Argument 1 Error - Not Readable!"; exit 2; fi


FILENAME="${1}";
FULLNAME="${2}";
NICKNAME="${3}";

USERNAME=$(cat "/etc/passwd" | grep -c "${FULLNAME}");



NUMBER=$(cat "/etc/passwd" | grep -c "${FULLNAME}");

if [[ "${NUMBER}" -eq 2 ]]; then
    echo "User not found in the file!";

    exit 3;
fi



if [[ "${NUMBER}" -ge 1 ]]; then
    index=1

    while read line; do
        echo "${index}. ${line}";

        array[index]=${line};

        index=$(( index + 1 ))
    done < <(cat /etc/passwd | grep "${FULLNAME}" | awk -F ':' '{ print $1; }');

    echo "0. Exit";

    read -r -p "Choose from 1-${NUMBER}: " choice;

    if [[ ${choice} -lt 0           ]]; then echo "Invalid choice - S!";    exit 4; fi
    if [[ ${choice} -gt "${NUMBER}" ]]; then echo "Invalid choice - B!";    exit 4; fi
    if [[ ${choice} -eq 0           ]]; then echo "Oh, bye... See you!";    exit 4; fi

    USERNAME="${array[${choice}]}";
fi



echo "${NICKNAME}" "${USERNAME}" >> "${FILENAME}";
