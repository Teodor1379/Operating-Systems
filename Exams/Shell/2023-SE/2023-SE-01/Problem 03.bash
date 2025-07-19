#!/bin/bash



# 2023-SE-01



if [[ "${#}" -ne 2 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



if [[ ! -f "${1}" ]]; then
    echo "Грешка на Аргумен 1 - НЕ Е ФАЙЛ!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Грешка на Аргумен 1 - НЕ Е ЧЕТИМ!";
    
    exit 3;
fi



if [[ ! -d "${2}" ]]; then
    echo "Грешка на Аргумент 2 - НЕ Е ДИРЕКТОРИЯ!";

    exit 3;
fi

if [[ ! -r "${2}" ]]; then
    echo "Грешка на Аргумент 2 - НЕ Е ЧЕТИМА!";

    exit 3
fi



RESULT=$(find "${2}" -mindepth 1 -maxdepth 2 -type f -name "*.txt" 2> /dev/null);

for file in $RESULT; do
    CONTENT=$(cat "${file}")

    if [[ $(basename "${file}") == "${1}" ]]; then
        continue;
    fi

    while IFS= read -r word; do
        if [[ -z "${word}" ]]; then
            continue
        fi

        replacement=$(echo "${word}" | tr '[:alpha:]' '*' | tr "[:digit:]" '*' | tr '_' '*');

        CONTENT=$(echo "${CONTENT}" | sed -E "s/\b${word}\b/${replacement}/gi");
    done < "${1}";

    echo "${CONTENT}" > "${file}";
done
