#!/bin/bash



# 05-b-9600



option="${1}";



for file in "${@}"; do
    archive=$(date +"%y-%m-%d-%H-%M-%S")

    if [[ -f "${file}" ]]; then
        name=$(basename "${file}");

        echo "[${archive}] Removed file ${file}";

        tar -z -f "${BACKUP_DIR}/${name}_${archive}.gz" "${file}";

        rm "${file}";
    elif [[ -d "${file}" ]]; then
        name=$(basename "${file}");

        entries=$(find "${file}" | wc -l);

        if [[ "${entries}" -eq 0 ]]; then
            echo "[${archive}] Removed directory ${file}.";

            tar -c -z -f "${BACKUP_DIR}/${name}_${archive}.tgz" "${file}";

            rmdir "${file}";
        else
            if [[ "${option}" == "-r" ]]; then
                echo "[${archive}] Removed directory ${file}.";

                tar -c -z -f "${BACKUP_DIR}/${name}_{$archive}.tgz" "${file}";

                rm -r -f "${option}";
            else
                echo "error: ${file} is not empty, will not delete";
            fi
        fi
    fi
done
