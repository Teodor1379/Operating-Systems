#!/bin/bash



# 05-b-7800



counter=0



while read -r file; do
    if [[ -x "${file}" ]]; then
        counter=$(( counter + 1 ));
    fi
done < <(find "$PATH" -type f);



echo "The number of executable files are: ${counter}.";
