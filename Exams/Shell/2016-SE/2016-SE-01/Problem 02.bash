#!/bin/bash



# 2016-SE-01



if [[ "${#}" -ne 1 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



if [[ ! -d "${1}" ]]; then
    echo "Грешка на Аргумента - НЕ Е ДИРЕКТОРИЯ!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Грешка на Аргумента - НЕ Е ЧЕТИМ!";

    exit 3;
fi



find "${1}" -mindepth 1 -maxdepth 2 -type l -exec test ! -e {} \; -print 2> /dev/null
