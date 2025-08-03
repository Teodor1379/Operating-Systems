#!/bin/bash



# 05-b-3100



read -r -p "Въведи низ: " username;



if ! "$(cat /etc/passwd | grep -q "${username}")"; then
    echo "Потребителят не е намерен!";

    exit 1;
fi



echo "Активни сесии: $(who | grep "${username}" | wc -l)";
