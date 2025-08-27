#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>

#include <err.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>



const char* ERROR_FILE_O = "Error while opening the file!";
const char* ERROR_FILE_C = "Error while closing the file!";
const char* ERROR_FILE_R = "Error while reading the file!";
const char* ERROR_FILE_W = "Error while writing the file!";




const char* file1 = "/etc/passwd";
const char* file2 = "./etcpasswd";



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



void closingAllSafe(void);



int readingSafe(const char*, int, void*, size_t);
int writingSafe(const char*, int, void*, size_t);



const uint8_t count = 2;

int descriptors[2] = { -1, -1 };



int main(void) {
    openingSafe(file1, O_RDONLY                     , S_IRUSR | S_IWUSR, &descriptors[0]);
    openingSafe(file2, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR, &descriptors[1]);


    while (1) {
        char c = 0;

        int reading = readingSafe(file1, descriptors[0], &c, sizeof(char));

        if (reading == 0) {
            break;
        }

        if (c == ':') {
            c = '?';
        }

        writingSafe(file2, descriptors[1], &c, sizeof(char));
    }


    closingAllSafe();


    exit(EXIT_SUCCESS);
}



void openingSafe(const char* filePath, int flags, mode_t mode, int* descriptor) {
    *descriptor = open(filePath, flags, mode);

    if (*descriptor == -1) {
        closingAllSafe();

        errx(2, "%s: %s", ERROR_FILE_O, filePath);
    }
}

void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int closing = close(descriptor);

        if (closing == -1) {
            warn("%s: %d", ERROR_FILE_C, descriptor);
        }
    }

    errno = oldErrno;
}



void closingAllSafe() {
    for (uint8_t i = 0; i < count; ++i) {
        closingSafe(descriptors[i]);
    }
}



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    int result = read(descriptor, memory, size);

    if (result == -1) {
        closingAllSafe();

        errx(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        closingAllSafe();

        errx(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
