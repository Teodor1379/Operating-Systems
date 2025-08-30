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

const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_WAIT = "Error while wait command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";
const char* ERROR_WAIT_EXTSTS = "Error while waiting - extsts!";



int executingWaitCommand(int*);



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



int readingSafe(const char*, int,       void*, size_t);
int writingSafe(const char*, int, const void*, size_t);



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }

    const char* file = argv[1]  ;
    const char* text = "foobar" ;

    pid_t pid = fork();

    if (pid < 0) {
        err(1, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        int descriptor = 0;

        openingSafe(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, &descriptor);

        writingSafe(file, descriptor, text, sizeof(char) * 6);

        closingSafe(descriptor);

        exit(EXIT_SUCCESS);
    } else {
        int status = 0;

        executingWaitCommand(&status);

        int descriptor = 0;

        openingSafe(file, O_RDONLY, S_IRUSR | S_IWUSR, &descriptor);

        while (1) {
            char c1 = 0;
            char c2 = 0;

            if (readingSafe(file, descriptor, &c1, sizeof(char)) == 0) {
                break;
            }

            writingSafe("Standard Output", 1, &c1, sizeof(char));

            if (readingSafe(file, descriptor, &c2, sizeof(char)) == 0) {
                break;
            }

            writingSafe("Standard Output", 1, &c2, sizeof(char));

            writingSafe("Standard Output", 1, " ", sizeof(char));
        }
    }
}



int executingWaitCommand(int* status) {
    assert(status !=    NULL);

    int result = wait(status);

    if (result < 0) {
        err(4, "%s", ERROR_WAIT);
    }

    if (WIFEXITED(*status) == 0 && WIFSTOPPED(*status) == 0 && WIFSIGNALED(*status) == 0) {
        errx(3, "%s", ERROR_WAIT_STATUS);
    }

    if (WEXITSTATUS(*status) != 0) {
        errx(4, "%s", ERROR_WAIT_EXTSTS);
    }

    return result;
}



void openingSafe(const char* filePath, int flags, mode_t rights, int* descriptor) {
    assert(filePath     !=  NULL);
    assert(descriptor   !=  NULL);

    *descriptor = open(filePath, flags, rights);

    if (*descriptor < 0) {
        err(2, "%s: %s", ERROR_FILE_O, filePath);
    }
}

void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int result = close(descriptor);

        if (result < 0) {
            errx(2, "%s:%d", ERROR_FILE_C, descriptor);
        }
    }

    errno = oldErrno;
}



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result < 0) {
        err(3, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, const void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result < 0 || (size_t)(result) != size) {
        err(4, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
