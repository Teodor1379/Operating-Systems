#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>

#include <err.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>



const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_EXEC = "Error while exec command!";
const char* ERROR_WAIT = "Error while wait command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";
const char* ERROR_WAIT_EXTSTS = "Error while waiting - extsts!";



void executingForkCommand(const char*   );
void executingWaitCommand(int*          );



int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Expected Different Arguments!");
    }

    int status1 = 0;
    int status2 = 0;

    executingForkCommand(argv[1]);  executingWaitCommand(&status1); if (WEXITSTATUS(status1) != 0)  { exit(42); }
    executingForkCommand(argv[2]);  executingWaitCommand(&status2); if (WEXITSTATUS(status2) != 0)  { exit(42); }

    exit(EXIT_SUCCESS);
}



void executingForkCommand(const char* commandName) {
    assert(commandName  !=  NULL);

    pid_t pid = fork();

    if (pid < 0) {
        err(1, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        int result = execl(commandName, commandName, NULL);

        if (result < 0) {
            err(2, "%s", ERROR_EXEC);
        }

        exit(EXIT_SUCCESS);
    }
}

void executingWaitCommand(int* status) {
    assert(status   !=  NULL);

    int result = wait(status);

    if (result < 0) {
        err(3, "%s", ERROR_WAIT);
    }

    if (
        WIFEXITED   (*status)   ==  0   &&
        WIFSIGNALED (*status)   ==  0   &&
        WIFSTOPPED  (*status)   ==  0
    ) {
        errx(2, "%s", ERROR_WAIT_STATUS);
    }
}
