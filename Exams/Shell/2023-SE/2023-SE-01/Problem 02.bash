#!/bin/bash



if [[ "${#}" -ne 2 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



if [[ ! -f "${1}" ]]; then
    echo "Грешка на Аргумент 1 - НЕ Е ФАЙЛ!";

    exit 2;
fi

if [[ ! -r "${1}" ]]; then
    echo "Грешка на Аргумент 2 - НЕ Е ЧЕТИМ!";

    exit 3;
fi



RESULT=$(cat "${1}" | cut -d ',' -f 4,5 | grep -E ",${2}" | cut -d ',' -f 1 | sort | uniq -c | sort -n | tail -n 1 | awk '{ print $2; }');

if [[ -z "${RESULT}" ]]; then
    echo "Не са намерени звезди с искания тип!";

    exit 4;
fi



STAR_NAME="";
STAR_MAGN="";

while IFS=',' read -r name _ _ constellation _ _ magn; do
    if [[ "${magn}" == "--" ]]; then
        continue;
    fi

    if [[ "${RESULT}" != "${constellation}" ]]; then
        continue;
    fi

    if [[ -z "${STAR_NAME}" ]]; then
        STAR_NAME="${name}";
        STAR_MAGN="${magn}";
    else
        if [[ $(echo "${magn} < ${STAR_MAGN}" | bc -l) -eq 1 ]]; then
            STAR_NAME="${name}";
            STAR_MAGN="${magn}";
        fi
    fi
done < "${1}"



echo "Най-ярката звезда е ${STAR_NAME} с яркост ${STAR_MAGN}!";
