#!/bin/bash



# 05-b-3200



read -r "Enter the full path to a directory:" directory;



if [[ ! -d "${directory}" ]]; then
    echo "The string is not a directory!";

    exit 1;
fi



if [[ ! -r "${directory}" ]]; then
    echo "The directory is not readable!";

    exit 2;
fi



countF=$(find "${directory}" -type f 2>&1 | wc -l);
countD=$(find "${directory}" -type d 2>&1 | wc -l);



echo "The number of files F is: ${countF}.";
echo "The number of files D is: ${countD}.";
