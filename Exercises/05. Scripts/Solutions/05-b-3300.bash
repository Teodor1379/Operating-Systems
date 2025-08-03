#!/bin/bash



# 05-b-3300



read -r "Enter the name of File 1: " file1;
read -r "Enter the name of File 2: " file2;
read -r "Enter the name of File 3: " file3;




if [[ ! -f "${file1}" ]]; then
    echo "String 1 is not a file!";

    exit 1;
fi

if [[ ! -f "${file2}" ]]; then
    echo "String 2 is not a file!";

    exit 1;
fi

if [[ ! -f "${file3}" ]]; then
    echo "String 3 is not a file!";

    exit 1;
fi



if [[ ! -r "${file1}" ]]; then
    echo "File 1 is not readable!";

    exit 2;
fi

if [[ ! -r "${file2}" ]]; then
    echo "File 2 is not readable!";

    exit 2;
fi



if [[ ! -w "${file3}" ]]; then
    echo "File 3 is not writable!";

    exit 3;
fi



paste "${file1}" "${file2}" | sort > "${file3}";
