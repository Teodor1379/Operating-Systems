#include <assert.h>

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



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



void closingSafeAllDesc(void);



int readingSafe(const char*, int, void*, size_t);
int writingSafe(const char*, int, void*, size_t);



const uint8_t count = 1;

int descriptors[1] = { -1 };



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }


    const char* file = argv[1];

    openingSafe(file, O_RDONLY, S_IRUSR, &descriptors[0]);


    char c = 0; unsigned int lines = 0;

    while (1) {
        int reading = readingSafe(file, descriptors[0], &c, sizeof(char));

        if (reading == 0) {
            break;
        }

        writingSafe("Standard Output", 1, &c, sizeof(char));

        if (c == '\n') {
            lines = lines + 1;
            
            if (lines == 10) {
                break;
            }
        }
    }


    closingSafeAllDesc();


    exit(EXIT_SUCCESS);
}



void openingSafe(const char* filePath, int modes, mode_t rights, int* memory) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    *memory = open(filePath, modes, rights);

    if (*memory < 0) {
        closingSafeAllDesc();

        errx(2, "%s: %s", ERROR_FILE_O, filePath);
    }
}




void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int closing = close(descriptor);

        if (closing == -1) {
            warnx("%s: %d", ERROR_FILE_C, descriptor);
        }
    }

    errno = oldErrno;
}

void closingSafeAllDesc(void) {
    for (uint8_t i = 0; i < count; ++i) {
        closingSafe(descriptors[i]);
    }
}



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result == -1) {
        closingSafeAllDesc();

        errx(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || result != sizeof(size)) {
        closingSafeAllDesc();

        err(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
