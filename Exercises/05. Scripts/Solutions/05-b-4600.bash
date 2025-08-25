#!/bin/bash



# 05-b-4600



if [[ "${#}" -ne 3 ]]; then
    echo "Expected Different Arguments!";

    exit 4;
fi



number1="${1}";
number2="${2}";
number3="${3}";



if [[ ! "${number1}" =~ ^(-){0,1}[0-9]+$ ]]; then echo "Argument 1 Error - Not a Number!";  exit 3; fi
if [[ ! "${number2}" =~ ^(-){0,1}[0-9]+$ ]]; then echo "Argument 2 Error - Not a Number!";  exit 3; fi
if [[ ! "${number3}" =~ ^(-){0,1}[0-9]+$ ]]; then echo "Argument 3 Error - Not a Number!";  exit 3; fi




if [[ "${number2}" -gt "${number3}" ]]; then
    echo "Inverted Interval Limits!";

    exit 2;
fi



if [[ "${number1}" -lt "${number2}" ]]; then    echo "The number is not in the interval!";  exit 1; fi
if [[ "${number1}" -gt "${number3}" ]]; then    echo "The number is not in the interval!";  exit 1; fi



echo "The number is in the interval!";  exit 0;
