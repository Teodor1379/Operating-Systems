#!/bin/bash



# 2016-SE-01



SPECIAL_NAME="philip-j-fry.txt"



if [[ $# -ne 1 ]]; then
    echo "Невалиден брой Аргументи";

    exit 1;
fi

if [[ ! -f "$1" ]]; then
    echo "Грешка на Аргумента - НЕ Е ФАЙЛ!";

    exit 2;
fi

if [[ ! -r "$1" ]]; then
    echo "Грешка на Аргумента - НЕЧЕТИМ!";

    exit 3;
fi

if [[ "$1" !=  "$SPECIAL_NAME" ]]; then
    echo "Грешка на Аргумента - НЕВАЛИДНО ИМЕ!";

    exit 4;
fi



RESULT=$(cat ${SPECIAL_NAME} | grep -E "[0,2,4,6,8]+" | grep -v -E "[a-w]+" | wc -l);

echo "Броят на търсените редове е ${RESULT}.";
