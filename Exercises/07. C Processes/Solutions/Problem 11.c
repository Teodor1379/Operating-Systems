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



const char* ERROR_FILE_W = "Error while writing the file!";

const char* ERROR_EXEC = "Error while exec command!";
const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_WAIT = "Error while wait command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";



void executeForkCommand(const char* );
void executeWaitCommand(int*        );



int main(int argc, char* argv[]) {
    if (argc == 1) {
        errx(1, "Expected Different Arguments");
    }

    int counterFail = 0;
    int counterSucc = 0;

    for (int i = 1; i < argc; ++i) {
        int status = 0;

        pid_t pid = fork();

        if (pid < 0) {
            err(1, "%s", ERROR_FORK);
        }

        if (pid == 0) {
            executeForkCommand(argv[i]);
        }

        executeWaitCommand(&status);

        counterFail = counterFail + (WEXITSTATUS(status) != 0);
        counterSucc = counterSucc + (WEXITSTATUS(status) == 0);
    }

    char buffer1[64] = { 0 };   int length1 = snprintf(buffer1, sizeof(buffer1), "Succ Processes Number: %d\n", counterSucc);
    char buffer2[64] = { 0 };   int length2 = snprintf(buffer2, sizeof(buffer2), "Fail Processes Number: %d\n", counterFail);

    if (write(1, buffer1, length1) != length1) { err(4, "Error while printing result!");    }
    if (write(2, buffer2, length2) != length2) { err(4, "Error while printing result!");    }

    exit(EXIT_SUCCESS);
}



void executeForkCommand(const char* commandName) {
    assert(commandName  !=  NULL);

    int result = execl(commandName, commandName, NULL);

    if (result < 0) {
        err(2, "%s", ERROR_EXEC);
    }
}

void executeWaitCommand(int* status) {
    assert(status   !=  NULL);

    int result = wait(status);

    if (result < 0) {
        err(3, "%s", ERROR_WAIT);
    }

    if (
        WIFEXITED   (*status)   !=  0   &&
        WIFSIGNALED (*status)   !=  0   &&
        WIFSTOPPED  (*status)   !=  0
    ) {
        errx(2, "%s", ERROR_WAIT_STATUS);
    }
}
