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
const char* ERROR_FILE_T = "Error while trncing the file!";



void    openingSafe(const char*, int, mode_t, int*  );
void    closingSafe(int                             );



void    closingAllSafe(void);



int     readingSafe(const char*, int, void*, size_t );
int     writingSafe(const char*, int, void*, size_t );
int     seekingSafe(const char*, int, off_t, int    );



const uint8_t count = 3;

int descriptors[3] = { -1, -1, -1 };



void copyContent(int*, int*, const char*, const char*);



int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Expected Different Arguments!");
    }


    const char* file1 = argv[1];
    const char* file2 = argv[2];
    const char* file3 = "TEMPF";

    openingSafe(file1, O_RDONLY | O_CREAT           , S_IRUSR | S_IWUSR, &descriptors[0]);
    openingSafe(file2, O_RDONLY | O_CREAT           , S_IRUSR | S_IWUSR, &descriptors[1]);
    openingSafe(file3, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR, &descriptors[2]);


    copyContent(&descriptors[0], &descriptors[2], file1, file3);
    copyContent(&descriptors[1], &descriptors[0], file2, file1);
    copyContent(&descriptors[2], &descriptors[1], file3, file2);



    closingAllSafe();

    int result = remove(file3);

    if (result < 0) {
        errx(6, "%s: %s", "Error while removing the file!", file3);
    }


    exit(EXIT_SUCCESS);
}



void openingSafe(const char* filePath, int flags, mode_t modes, int* memory) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);
    
    *memory = open(filePath, flags, modes);

    if (*memory == -1) {
        closingAllSafe();

        errx(2, "%s: %s", ERROR_FILE_O, filePath);
    }
}

void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int result = close(descriptor);

        if (result == -1) {
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
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result == -1) {
        closingAllSafe();

        errx(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        closingAllSafe();

        errx(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}

int seekingSafe(const char* filePath, int descriptor, off_t offset, int flags) {
    assert(filePath !=  NULL);

    int result = lseek(descriptor, offset, flags);

    if (result == -1) {
        closingAllSafe();

        errx(5, "%s: %s", ERROR_FILE_S, filePath);
    }

    return result;
}



void copyContent(int* descriptor1, int* descriptor2, const char* filePath1, const char* filePath2) {
    assert(descriptor1  !=  NULL);
    assert(descriptor2  !=  NULL);
    assert(filePath1    !=  NULL);
    assert(filePath2    !=  NULL);

    seekingSafe(filePath1, *descriptor1, 0, SEEK_SET);

    while (1) {
        char c = 0;

        int reading = readingSafe(filePath1, *descriptor1, &c, sizeof(char));

        if (reading == 0) {
            break;
        }

        writingSafe(filePath2, *descriptor2, &c, sizeof(char));
    }

    closingSafe(*descriptor1);  openingSafe(filePath1, O_WRONLY, S_IRUSR | S_IWUSR, descriptor1);
    closingSafe(*descriptor2);  openingSafe(filePath2, O_RDONLY, S_IRUSR | S_IWUSR, descriptor2);
}
