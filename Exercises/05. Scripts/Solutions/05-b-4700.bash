#!/bin/bash



# 05-b-4700



if [[ "${#}" -gt 2 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



num="${1}";
del="${2}";



if [[ ! "${num}" =~ ^[1-9]{1}[0-9]*$ && ! "${num}" =~ ^(0){1}$ ]]; then
    echo "Argument 1 Error - Not a Number!";

    exit 2;
fi



if [[ "${del}" == "" ]]; then
    del=" ";
fi



digits=$(echo "${num}" | grep -o -E '.' | wc -l );
revers=$(echo "${num}" | grep -o -E '.'         );



countr="${digits}"  ;
result=""           ;

while read -r line; do
    countr=$(( countr - 1 ));

    if (( countr > 0 && countr % 3 == 0 )); then
        result="${result}${line}${del}";
    else
        result="${result}${line}";
    fi
done < <(echo "${revers}");



echo "$result";
