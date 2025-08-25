#!/bin/bash



# 05-b-9500



if [[ "${#}" -gt 2 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



col="";
txt="";

if [[ -z "${2}" ]]; then
    txt="${1}";
else
    col="${1}";
    txt="${2}";
fi


if [[ -z "${col}" ]]; then
    echo -e "${txt}";
elif [[ "${col}" == "-r" ]]; then
    echo -e "\033[0;31m ${txt}";
elif [[ "${col}" == "-g" ]]; then
    echo -e "\033[0;32m ${txt}";
elif [[ "${col}" == "-b" ]]; then
    echo -e "\033[0;34m ${txt}";
else
    echo -e "Unknown colour!";
fi



echo -e '\033[0m';
