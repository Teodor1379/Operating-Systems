#!/bin/bash



# 05-b-7000



if [[ "${#}" -eq 0 ]]; then
    echo "Невалиден Брой Аргументи!";

    exit 1;
fi



for file in "${@}"; do
    if [[ ! -f "${file}" ]]; then
        echo "Грешка на Аргумента ${file} - НЕ Е ФАЙЛ!";
    
        exit 2;
    fi

    if [[ ! -r "${file}" ]]; then
        echo "Грешка на Аргумента ${file} - НЕ Е ЧЕТИМ!";

        exit 3;
    fi
done



read -r -p "Въведете символния низ: " string_pattern;



for file in "${@}"; do
    number_lines=$(cat "${file}" | grep -c -F "${string_pattern}");

    echo "Файлът ${file} съдържа низа ${number_lines} пъти!";
done
