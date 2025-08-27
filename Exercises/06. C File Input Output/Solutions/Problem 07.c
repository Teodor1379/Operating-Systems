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
const char* ERROR_FILE_Z = "Error while stating the file!";



void checkDirectory(const char*);




void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



void closingAllSafe(void);



int readingSafe(const char*, int, void*, size_t);
int writingSafe(const char*, int, void*, size_t);



const uint8_t count = 2;

int descriptors[2] = { -1, -1 };



int main(int argc, char* argv[]) {
    if (argc < 3) {
        errx(1, "Expected Different Arguments!");
    }


    const char* dir = argv[argc - 1];

    checkDirectory(dir);



    char* directoryName = NULL;

    if (dir[strlen(dir) - 1] != '/') {
        directoryName = malloc(strlen(dir) + 1);

        strcpy(directoryName, dir);
        strcat(directoryName, "/");
    } else {
        directoryName = malloc(strlen(dir));

        strcpy(directoryName, dir);
    }



    for (int i = 1; i < (argc - 1); ++i) {
        const char* file = argv[i];

        char* target = malloc(strlen(directoryName) + strlen(file) + 1);

        strcpy(target, directoryName);
        strcat(target, file         );

        
        openingSafe(file    , O_RDONLY                  , S_IRUSR           , &descriptors[0]);
        openingSafe(target  , O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR , &descriptors[1]);

        while (1) {
            char c = 0;

            int reading = readingSafe(file, descriptors[0], &c, sizeof(char));

            if (reading == 0) {
                break;
            }

            writingSafe(file, descriptors[1], &c, sizeof(char));
        }

        closingAllSafe();


        free(target);
    }


    free(directoryName);


    exit(EXIT_SUCCESS);
}



void checkDirectory(const char* filePath) {
    assert(filePath !=  NULL);

    struct stat directoryStats;

    int result = stat(filePath, &directoryStats);

    if (result == -1) {
        err(2, "%s: %s", ERROR_FILE_Z, filePath);
    }

    if (S_ISDIR(directoryStats.st_mode) == 0) {
        err(3, "%s: %s", "Error from the type of the file:", filePath);
    }
}



void openingSafe(const char* filePath, int flags, mode_t mode, int* descriptor) {
    assert(filePath     !=  NULL);
    assert(descriptor   !=  NULL);

    *descriptor = open(filePath, flags, mode);

    if (*descriptor == -1) {
        closingAllSafe();

        errx(4, "%s: %s", ERROR_FILE_O, filePath);
    }
}

void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int closing = close(descriptor);

        if (closing == -1) {
            warn("%s: %d", ERROR_FILE_W, descriptor);
        }
    }

    errno = oldErrno;
}



void closingAllSafe(void) {
    for (uint8_t i = 0; i < count; ++i) {
        closingSafe(descriptors[i]);
    }
}



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        closingAllSafe();

        errx(5, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1) {
        closingAllSafe();

        errx(6, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
