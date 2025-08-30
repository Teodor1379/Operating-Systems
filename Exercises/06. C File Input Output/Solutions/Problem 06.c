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



int readingSafe(const char*, int, void*, size_t);
int writingSafe(const char*, int, void*, size_t);



int main(int argc, char* argv[]) {
    if (argc == 1) {
        errx(1, "Expected Different Arguments!");
    }


    for (int i = 1; i < argc; ++i) {
        int currentDescriptor = -1;

        openingSafe(argv[i], O_RDONLY, S_IRUSR, &currentDescriptor);

        while (1) {
            char c = 0;

            int reading = readingSafe(argv[i], currentDescriptor, &c, sizeof(c));

            if (reading == 0) {
                break;
            }

            writingSafe("Standard Output", 1, &c, sizeof(c));
        }

        closingSafe(currentDescriptor);
    }


    exit(EXIT_SUCCESS);
}



void openingSafe(const char* filePath, int flags, mode_t mode, int* descriptor) {
    assert(filePath     !=  NULL);
    assert(descriptor   !=  NULL);

    *descriptor = open(filePath, flags, mode);

    if (*descriptor < 0) {
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



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result == -1) {
        closingSafe(descriptor);

        errx(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        closingSafe(descriptor);

        errx(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
