#!/bin/bash



if [[ "${#}" -lt 2 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



if ! [[ "${1}" =~ ^[0-9]+$ ]]; then
    echo "Грешка на Аргумент 1 - НЕ Е ЧИСЛО!";

    exit 2;
fi



CURRENT_TIME=0;
NUMBER_ITERS=0;



DURATION="${1}";

shift;



while true; do
    if [[ $(echo "${CURRENT_TIME} > ${DURATION}" | bc -l) -eq 1 ]]; then
        break;
    fi

    B_TIME=$(date +%s.%N);

    "$@" > /dev/null 2>&1;

    A_TIME=$(date +%s.%N);

    ELAPSED=$(echo "${A_TIME} - ${B_TIME}" | bc -l);

    CURRENT_TIME=$(echo "scale=2; ${CURRENT_TIME} + ${ELAPSED}" | bc -l);
    NUMBER_ITERS=$(echo "scale=2; ${NUMBER_ITERS} + 1"          | bc -l);
done



AVERAGE_TIME=$(echo "scale=2; ${CURRENT_TIME} / ${NUMBER_ITERS}" | bc -l);



LC_ALL=C printf "Ran the command '%s' %d times for %.2f seconds.\n" "${*}" "${NUMBER_ITERS}" "${CURRENT_TIME}"  ;
LC_ALL=C printf "Average runtime: %.2f seconds.\n"                  "${AVERAGE_TIME}"                           ;
