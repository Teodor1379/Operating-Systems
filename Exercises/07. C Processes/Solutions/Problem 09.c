#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>

#include <err.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>




const char* ERROR_FILE_O = "Error while opening the file!";
const char* ERROR_FILE_C = "Error while closing the file!";
const char* ERROR_FILE_R = "Error while reading the file!";
const char* ERROR_FILE_W = "Error while writing the file!";

const char* ERROR_FORK = "Error while forking command!";
const char* ERROR_WAIT = "Error while waiting command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";
const char* ERROR_WAIT_EXTSTS = "Error while waiting - extsts!";



void executingForkCommand(const char*, int*, const char*);
void executingWaitCommand(int*                          );



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



int readingSafe(const char*, int,       void*, size_t);
int writingSafe(const char*, int, const void*, size_t);



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }

    const char* filePath = argv[1];

    int descriptor = 0;

    openingSafe(filePath, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, &descriptor);

    close(descriptor);


    int status1 = 0;    int descriptor1 =   0;
    int status2 = 0;    int descriptor2 =   0;

    executingForkCommand(filePath, &descriptor1, "foo");    executingWaitCommand(&status1);
    executingForkCommand(filePath, &descriptor2, "bar");    executingWaitCommand(&status2);
    
    return 0;
}



void executingForkCommand(const char* filePath, int* descriptor, const char* string) {
    assert(filePath !=  NULL);
    assert(string   !=  NULL);

    int pid = fork();

    if (pid < 0) {
        err(5, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        openingSafe(filePath, O_WRONLY | O_APPEND, S_IRWXU, descriptor);

        writingSafe(filePath, *descriptor, string, sizeof(char) * strlen(string));

        closingSafe(*descriptor);

        exit(EXIT_SUCCESS);
    }
}

void executingWaitCommand(int* status) {
    assert(status   !=  NULL);

    int result = wait(status);

    if (result < 0) {
        err(6, "%s", ERROR_WAIT);
    }

    if (WIFEXITED(*status) == 0 && WIFSTOPPED(*status) == 0 && WIFSIGNALED(*status) == 0) {
        errx(2, "%s", ERROR_WAIT_STATUS);
    }

    if (WEXITSTATUS(*status) != 0) {
        errx(3, "%s", ERROR_WAIT_EXTSTS);
    }
}



void openingSafe(const char* filePath, int flags, mode_t mode, int* descriptor) {
    assert(filePath     !=  NULL);
    assert(descriptor   !=  NULL);

    *descriptor = open(filePath, flags, mode);

    if (*descriptor < 0) {
        err(2, "%s: %s", ERROR_FILE_O, filePath);
    }
}

void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int result = close(descriptor);

        if (result < 0) {
            warn("%s:%d", ERROR_FILE_C, descriptor);
        }
    }

    errno = oldErrno;
}



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result < 0) {
        closingSafe(descriptor);

        err(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, const void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result < 0 || (size_t)(result) != size) {
        closingSafe(descriptor);

        err(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
