#!/bin/bash



# 2023-SE-02



if [[ "${#}" -ne 3 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



if [[ ! -f "${1}" || ! -f "${2}" ]]; then
    echo "Грешка на Аргументите - НЕ СА ФАЙЛОВЕ!";

    exit 2;
fi

if [[ ! -r "${1}" || ! -r "${2}" ]]; then
    echo "Грешка на Аргументите - НЕ СА ЧЕТИМИ!";

    exit 3;
fi



ROW1=$(cat "${1}" | grep -F "${3}:");
ROW2=$(cat "${2}" | grep -F "${3}:");

if [[ -z "${ROW1}" ]]; then
    echo "Не съществува запис за черната дупка в ${1}!";

    exit 4;
fi

if [[ -z "${ROW2}" ]]; then
    echo "Не съществува запис за черната дупка в ${2}!";

    exit 4;
fi



DISTANCE1=$(echo "${ROW1}" | cut -d ':' -f 2- | awk '{ print $1; }');
DISTANCE2=$(echo "${ROW2}" | cut -d ':' -f 2- | awk '{ print $1; }');

if (( DISTANCE1 < DISTANCE2 )); then
    echo "${1}";
elif (( DISTANCE1 > DISTANCE2 )); then
    echo "${2}";
else
    echo "Равно Разстояние: ${1}";
fi
