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



const unsigned int count = 1;

int descriptors[1] = { -1 };



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



void closingSafeAllDesc(void);



int readingSafe(const char*, int, void*, size_t);
int writingSafe(const char*, int, void*, size_t);



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }


    const char* file = argv[1];

    openingSafe(file, O_RDONLY, S_IRUSR, &descriptors[0]);


    unsigned int numberChars = 0;
    unsigned int numberWords = 0;
    unsigned int numberLines = 0;

    char c = 0;
    
    int inWord = 0;

    while (1) {
        int reading = readingSafe(file, descriptors[0], &c, sizeof(char));

        if (reading == 0) {
            break;
        }

        numberChars = numberChars + 1;

        if (c != ' ' && c != '\t' && c != '\n') {
            if (inWord == 0) {
                numberWords = numberWords + 1;

                inWord = 1;
            }
        } else {
            inWord = 0;
        }

        if (c == '\n') {
            numberLines = numberLines + 1;
        }
    }



    char buffer[256] = { 0 };

    snprintf(buffer, sizeof(buffer), "Number of chars are: %u.\n", numberChars);    writingSafe("Standard Output", 1, buffer, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Number of words are: %u.\n", numberWords);    writingSafe("Standard Output", 1, buffer, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Number of lines are: %u.\n", numberLines);    writingSafe("Standard Output", 1, buffer, sizeof(buffer));


    closingSafeAllDesc();


    exit(EXIT_SUCCESS);
}



void openingSafe(const char* filePath, int flags, mode_t modes, int* memory) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    *memory = open(filePath, flags, modes);

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
            warn("%s: %d", ERROR_FILE_C, descriptor);
        }
    }

    errno = oldErrno;
}



void closingSafeAllDesc() {
    for (uint8_t i = 0; i < count; ++i) {
        close(descriptors[i]);
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

    if (result == -1 || (size_t)(result) != size) {
        closingSafeAllDesc();

        errx(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
