#!/bin/bash



# 05-b-7100



if [[ "${#}" -ne 2 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



if [[ ! -d "${1}" ]]; then
    echo "Грешка на Аргумент 1 - НЕ Е ДИРЕКТОРИЯ!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Грешка на Аргумент 1 - НЕ Е ЧЕТИМ!";

    exit 3;
fi



if ! [[ "${2}" =~ ^[0-9]+$ ]]; then
    echo "Грешка на Аргумент 2 - НЕ Е ЧИСЛО!";

    exit 4;
fi



FILES=$(find "${1}" -mindepth 1 -maxdepth 1 -type f 2> /dev/null);



for file in $FILES; do
    if [[ $(find "${file}" -printf "%s" ) -gt "${2}" ]]; then
        echo "Файлът ${file} има размер, който е по-голям от подаденото число!";
    fi
done
