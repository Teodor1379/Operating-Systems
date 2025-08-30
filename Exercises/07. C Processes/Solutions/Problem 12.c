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

const char* ERROR_EXEC = "Error while exec command!";
const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_WAIT = "Error while wait command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            );



void writingSafe(const char*, int, const void*, size_t);



void executingForkCommand(const char*   );
void executingWaitCommand(int*          );



int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Expected Different Arguments!");
    }

    const char* commandArg1 = argv[1];
    const char* commandArg2 = argv[2];
    const char* filePathArg = argv[3];

    int descriptor = 0;
    
    openingSafe(filePathArg, O_CREAT | O_TRUNC, S_IRWXU, &descriptor);

    closingSafe(descriptor);

    int status1 = 0;
    int status2 = 0;

    executingForkCommand(commandArg1);  executingWaitCommand(&status1);
    executingForkCommand(commandArg2);  executingWaitCommand(&status2);

    openingSafe(filePathArg, O_WRONLY | O_APPEND, S_IRWXU, &descriptor);

    if (WEXITSTATUS(status1) == 0) { writingSafe(filePathArg, descriptor, commandArg1, sizeof(char) * strlen(commandArg1)); writingSafe(filePathArg, descriptor, "\n", sizeof(char));   } else { warnx(2, "The command did not succeed!");   }
    if (WEXITSTATUS(status2) == 0) { writingSafe(filePathArg, descriptor, commandArg2, sizeof(char) * strlen(commandArg2)); writingSafe(filePathArg, descriptor, "\n", sizeof(char));   } else { warnx(2, "The command did not succeed!");   }

    return 0;
}



void openingSafe(const char* filePath, int flags, mode_t mode, int* descriptor) {
    assert(filePath     !=  NULL);
    assert(descriptor   !=  NULL);

    *descriptor = open(filePath, flags, mode);

    if (*descriptor < 0) {
        err(1, "%s: %s", ERROR_FILE_O, filePath);
    }
}

void closingSafe(int descriptor) {
    int oldErrno = errno;

    if (descriptor >= 0) {
        int result = close(descriptor);

        if (result < 0) {
            warnx("%s: %d", ERROR_FILE_C, descriptor);
        }
    }

    errno = oldErrno;
}



void writingSafe(const char* filePath, int descriptor, const void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result < 0 || (size_t)(result) != size) {
        closingSafe(descriptor);

        err(2, "%s: %s", ERROR_FILE_W, filePath);
    }
}



void executingForkCommand(const char* commandName) {
    assert(commandName != NULL);

    pid_t pid = fork();

    if (pid < 0) {
        err(3, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        int result = execl(commandName, commandName, NULL);

        if (result < 0) {
            err(3, "%s", ERROR_EXEC);
        }

        exit(EXIT_SUCCESS);
    }
}

void executingWaitCommand(int* status) {
    assert(status !=    NULL);

    int result = wait(status);

    if (result < 0) {
        err(5, "%s", ERROR_WAIT);
    }

    if (
        WIFEXITED   (*status)   ==  0   &&
        WIFSTOPPED  (*status)   ==  0   &&
        WIFSIGNALED (*status)   ==  0
    ) {
        errx(2, "%s", ERROR_WAIT_STATUS);
    }
}
