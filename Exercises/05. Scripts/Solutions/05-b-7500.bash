#!/bin/bash



# 05-b-7500



numbr=$RANDOM   ;
tries=0         ;



while true; do
    read -r -p "Guess? " guess;

    if [[ "${guess}" -lt "${numbr}" ]]; then
        echo "...bigger!";
    elif [[ "${guess}" -gt "${numbr}" ]]; then
        echo "...smaller!";
    else
        echo "RIGHT! Guessed ${numbr} in ${tries}!";

        break;
    fi
done
