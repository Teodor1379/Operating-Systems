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
const char* ERROR_FILE_S = "Error while seeking the file!";
const char* ERROR_FILE_T = "Error while stating the file!";

const char* ERROR_FILE_E = "Error while operating with the file - EMPTYFILE!";
const char* ERROR_FILE_P = "Error whole operating with the file - CORRUPTED!";



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



int readingSafe(const char*, int, void*, size_t );
int writingSafe(const char*, int, void*, size_t );
int seekingSafe(const char*, int, off_t, int    );



off_t readSizeBinaryFile(const char*, int);



void executeMinCommand(const char*);
void executeMaxCommand(const char*);
void executePrtCommand(const char*);



int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Expected Different Arguments!");
    }

    const char* cmnd = argv[1];
    const char* file = argv[2];

    if (strcmp(cmnd, "--min") == 0) {
        executeMinCommand(file);
    } else if (strcmp(cmnd, "--max") == 0) {
        executeMaxCommand(file);
    } else if (strcmp(cmnd, "--print") == 0) {
        executePrtCommand(file);
    } else {
        err(666, "Exepcted Different Argument!");
    }


    exit(EXIT_SUCCESS);
}



void openingSafe(const char* filePath, int flags, mode_t mode, int* descriptor) {
    assert(filePath     !=  NULL);
    assert(descriptor   !=  NULL);

    *descriptor = open(filePath, flags, mode);

    if (*descriptor == -1) {
        err(2, "%s: %s", ERROR_FILE_O, filePath);
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



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result == -1) {
        closingSafe(descriptor);

        err(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        closingSafe(descriptor);

        err(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}

int seekingSafe(const char* filePath, int descriptor, off_t offset, int flags) {
    assert(filePath !=  NULL);

    int result = lseek(descriptor, offset, flags);

    if (result == -1) {
        closingSafe(descriptor);

        err(5, "%s: %s", ERROR_FILE_S, filePath);
    }

    return result;
}



off_t readSizeBinaryFile(const char* filePath, int descriptor) {
    assert(filePath !=  NULL);

    struct stat fileStats;

    int result = stat(filePath, &fileStats);

    if (result == -1) {
        closingSafe(descriptor);

        err(6, "%s: %s", ERROR_FILE_T, filePath);
    }

    if (fileStats.st_size == 0) {
        closingSafe(descriptor);

        err(100, "%s: %s", ERROR_FILE_E, filePath);
    }

    if (fileStats.st_size % sizeof(uint16_t) != 0) {
        closingSafe(descriptor);

        err(200, "%s: %s", ERROR_FILE_P, filePath);
    }

    return fileStats.st_size / sizeof(uint16_t);
}



void executeMinCommand(const char* filePath) {
    assert(filePath !=  NULL);

    int descriptor = 0;     openingSafe(filePath, O_RDONLY, S_IRUSR, &descriptor);

    off_t size = readSizeBinaryFile(filePath, descriptor);

    unsigned char byte = 0; readingSafe(filePath, descriptor, &byte, sizeof(unsigned char));

    for (off_t i = 1; i < size; ++i) {
        unsigned char current = 0;

        readingSafe(filePath, descriptor, &current, sizeof(unsigned char));

        if (byte > current) {
            byte = current;
        }
    }

    char buffer[64] = { 0 };

    snprintf(buffer, sizeof(buffer), "The min element is: %d\n", byte);

    writingSafe("Standard Output", 1, buffer, sizeof(buffer));
}

void executeMaxCommand(const char* filePath) {
    assert(filePath !=  NULL);

    int descriptor = 0;     openingSafe(filePath, O_RDONLY, S_IRUSR, &descriptor);

    off_t size = readSizeBinaryFile(filePath, descriptor);

    unsigned char byte = 0; readingSafe(filePath, descriptor, &byte, sizeof(unsigned char));

    for (off_t i = 1; i < size; ++i) {
        unsigned char current = 0;

        readingSafe(filePath, descriptor, &current, sizeof(unsigned char));

        if (byte < current) {
            byte = current;
        }
    }

    char buffer[64] = { 0 };

    snprintf(buffer, sizeof(buffer), "The max element is: %d\n", byte);

    writingSafe("Standard Output", 1, buffer, sizeof(buffer));
}

void executePrtCommand(const char* filePath) {
    assert(filePath != NULL);

    int descriptor = 0;     openingSafe(filePath, O_RDONLY, S_IRUSR, &descriptor);

    off_t size = readSizeBinaryFile(filePath, descriptor);

    char buffer[64] = { 0 };

    for (off_t i = 0; i < size; ++i) {
        unsigned char byte = 0;

        readingSafe(filePath, descriptor, &byte, sizeof(unsigned char));

        snprintf(buffer, sizeof(buffer), "%c", byte);

        writingSafe("Standard Output", 1, &buffer, sizeof(buffer));
    }
}
