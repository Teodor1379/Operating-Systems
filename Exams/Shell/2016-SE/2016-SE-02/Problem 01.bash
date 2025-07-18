#!/bin/bash



# 2016-SE-02



if [[ "${#}" -ne 1 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi

if [[ ! "${1}" =~ ^[0-9]+$ ]]; then
    echo "Грешка на Аргумента - НЕ Е ЧИСЛО!";

    exit 2;
fi

if [[ $(whoami) != "root" ]]; then
    echo "Грешка на Скрипта - НЕ Е ROOT!";

    exit 3;
fi



USERS=$(ps -e -o uid= | sort -n | uniq);



for user in ${USERS}; do
    USED_MEMORY=$(ps -e -o uid=,rss= | awk -v current="${user}" \
        'BEGIN { memory = 0; } { if ($1 == current) { memory = memory + $2; } } END { print memory; }');

    echo -e "Потребител с UID ${user} използва RSS: ${USED_MEMORY} KB";
    
    if [[ "${USED_MEMORY}" -gt "${1}" ]]; then
        PROCESS=$(ps -e -o uid=,pid=,rss= | awk -v current="${user}" \
            'BEGIN { result = 0; maxPr = 0; } { if ($1 == current && maxPr < $3) { result = $2; max = $3 } } END { print result; }');

        echo "Прекратяване на процес ${PROCESS}!"; kill "${PROCESS}";

        if ps -p "{PROCESS}" > /dev/null; then
            echo "Процес ${PROCESS}$ не се прекрати - ще се прекрати със SIGKILL!"; kill -9 "${PROCESS}";
        fi
    fi
done
