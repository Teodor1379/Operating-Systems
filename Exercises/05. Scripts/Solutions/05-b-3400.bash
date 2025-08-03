#!/bin/bash



# 05-b-3400



read -r -p "Enter the file  : " filePt;
read -r -p "Enter the string: " string;



if [[ ! -f "${filePt}" ]]; then
    echo "The string is not a file!";

    exit 1;
fi



if [[ ! -r "${filePt}" ]]; then
    echo "File is not readable!";

    exit 2;
fi



cat "${filePt}" | grep -F -q "${string}";



echo "The status code is: ${?}";
