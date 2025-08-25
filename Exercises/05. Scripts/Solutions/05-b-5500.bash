#!/bin/bash



# 05-b-5500



username="Username"     ;
ggrpname="Group"        ;
shelname="Shell"        ;
gccsname="GECOS Field"  ;



echo -e "<table>";



echo -e "\t<tr>";

echo -e "\t\t<th>${username}</th>";
echo -e "\t\t<th>${ggrpname}</th>";
echo -e "\t\t<th>${shelname}</th>";
echo -e "\t\t<th>${gccsname}</th>";

echo -e "\t</tr>";



while read -r line; do
    username="$(                    echo "${line}" | cut -d ':' -f 1                    )"  ;
    ggrpname="$(getent group "$(    echo "${line}" | cut -d ':' -f 4)" | cut -d ':' -f 1)"  ;
    shelname="$(                    echo "${line}" | cut -d ':' -f 7                    )"  ;
    gccsname="$(                    echo "${line}" | cut -d ':' -f 5   | cut -d ',' -f 1)"  ;

    echo -e "\t<tr>";

    echo -e "\t\t<th>${username}</th>";
    echo -e "\t\t<th>${ggrpname}</th>";
    echo -e "\t\t<th>${shelname}</th>";
    echo -e "\t\t<th>${gccsname}</th>";

    echo -e "\t<tr>";
done < <(cat "/etc/passwd");
