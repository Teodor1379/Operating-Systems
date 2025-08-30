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



const char* ERROR_EXEC = "Error while exec command!";
const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_WAIT = "Error while wait command!";



void executeForkCommand(const char* );
int  executeWaitCommand(int*        );



int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Expected Different Arguments");
    }

    const char* commandName1 = argv[1];
    const char* commandName2 = argv[2];

    executeForkCommand(commandName1);
    executeForkCommand(commandName2);

    int status = 0;
    int firstF = 0;

    for (unsigned int i = 0; i < 2; ++i) {
        int result = executeWaitCommand(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && firstF == 0) {
            char buffer[16] = { 0 };

            int length = snprintf(buffer, sizeof(buffer), "%d\n", result);

            if (write(1, buffer, length * sizeof(char)) != length) {
                err(1, "%s", "Error while printing the result!");
            }

            firstF = 1;
        }
    }

    if (firstF == 0) {
        if (write(1, "-1\n", sizeof(char) * 3) != 3) {
            err(1, "%s", "Error while printing the result!");
        }
    }

    return 0;
}



void executeForkCommand(const char* commandName) {
    assert(commandName  !=  NULL);

    pid_t pid = fork();

    if (pid < 0) {
        err(2, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        int result = execl(commandName, commandName, NULL);

        if (result < 0) {
            err(3, "%s", ERROR_EXEC);
        }
    }
}

int executeWaitCommand(int* status) {
    assert(status   !=  NULL);

    int result = wait(status);

    if (result < 0) {
        err(4, "%s", ERROR_WAIT);
    }

    return result;
}
