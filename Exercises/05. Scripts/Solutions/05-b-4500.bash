#!/bin/bash



# 05-b-4500



if [[ "${#}" -ne 1 ]]; then
    echo "Expected Different Arguments!";

    exit 1;
fi



if [[ ! $(cat /etc/passwd | grep -q "${1}") ]]; then
    echo "User does not exist!";

    exit 2;
fi



while true; do
    if [[ $(who | grep -q "${1}") ]]; then
        echo "User ${1} logged in!";

        exit 0;
    fi

    sleep 1
done