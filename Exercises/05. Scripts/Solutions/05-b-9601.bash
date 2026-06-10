#!/bin/bash



if [[ -z "$BACKUP_DIR" ]]; then
    echo "Грешка: Не е въведена резервна директория!"
    exit 1
fi



if [[ ! -d "$BACKUP_DIR" ]]; then
    echo "Грешка: Директория ($BACKUP_DIR) не съществува!"
    exit 1
fi



if [[ "$1" == "-l" ]]; then
    for file in "$BACKUP_DIR"/*; do
        if [[ ! -e "$file" ]]; then
            continue;
        fi

        base=$(basename "$file")

        if [[ "$base" =~ ^(.*)_([0-9]{4})-([0-9]{2})-([0-9]{2})-([0-9]{2})-([0-9]{2})-([0-9]{2})\.(gz|tgz)$ ]]; then
            name="${BASH_REMATCH[1]}"

            Y="${BASH_REMATCH[2]}"
            M="${BASH_REMATCH[3]}"
            D="${BASH_REMATCH[4]}"
            h="${BASH_REMATCH[5]}"
            m="${BASH_REMATCH[6]}"
            s="${BASH_REMATCH[7]}"

            echo -e "${name}\t(${Y}/${M}/${D} ${h}:${m}:${s})"
        fi
    done

    exit 0
fi



if [[ -z "$1" ]]; then
    echo "Невалидно състояние на аргументите!"
    exit 1
fi



filename="$1"
target_dir="${2:-.}"



if [[ ! -d "$target_dir" ]]; then
    mkdir -p "$target_dir"
fi




declare -a matching_files
declare -a matching_dates
declare -a matching_types

for file in "$BACKUP_DIR"/*; do
    if [[ ! -e "$file" ]]; then
        continue;
    fi


    base=$(basename "$file")


    if [[ "$base" =~ ^(.*)_([0-9]{4})-([0-9]{2})-([0-9]{2})-([0-9]{2})-([0-9]{2})-([0-9]{2})\.(gz|tgz)$ ]]; then
        name="${BASH_REMATCH[1]}"

        if [[ "$name" == "$filename" ]]; then
            Y="${BASH_REMATCH[2]}"
            M="${BASH_REMATCH[3]}"
            D="${BASH_REMATCH[4]}"
            h="${BASH_REMATCH[5]}"
            m="${BASH_REMATCH[6]}"
            s="${BASH_REMATCH[7]}"
            ext="${BASH_REMATCH[8]}"
            matching_files+=("$file")
            matching_dates+=("(${Y}/${M}/${D} ${h}:${m}:${s})")
            matching_types+=("$ext")
        fi
    fi
done



N=${#matching_files[@]}



if [[ $N -eq 0 ]]; then
    echo "Грешка: Не са намерени резервни данни в '$filename'"
    exit 1
fi



choice=0



if [[ $N -eq 1 ]]; then
    choice=1
else
    for i in "${!matching_files[@]}"; do
        idx=$((i+1))
        echo "($idx) $filename  ${matching_dates[$i]}"
    done
    
    
    while true; do
        read -p "Избери си файл (1, $N): " choice

        if [[ "$choice" =~ ^[0-9]+$ ]] && [[ "$choice" -ge 1 ]] && [[ "$choice" -le "$N" ]]; then
            break
        else
            echo "Невалиден избор! Моля, избери си число между 1 и $N."
        fi
    done
fi



idx=$((choice-1))

chosen_file="${matching_files[$idx]}"
chosen_type="${matching_types[$idx]}"


if [[ "$chosen_type" == "gz" ]]; then
    gunzip -c "$chosen_file" > "${target_dir}/${filename}"
elif [[ "$chosen_type" == "tgz" ]]; then
    tar -xzf "$chosen_file" -C "$target_dir"
fi
