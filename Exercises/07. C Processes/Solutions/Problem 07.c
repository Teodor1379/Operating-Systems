#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>

#include <err.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>



const char* ERROR_FILE_W = "Error while writing the file!";

const char* ERROR_EXEC = "Error while execing command!";
const char* ERROR_FORK = "Error while forking command!";
const char* ERROR_WAIT = "Error while waiting command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";
const char* ERROR_WAIT_EXTSTS = "Error while waiting - extsts!";



void writingSafe(const char*, int, const void*, size_t);



void    executingCommandSafe(const char*, const char*   );
pid_t   executingCommandWait(int*                       );



int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Expected Different Arguments!");
    }


    for (int i = 1; i < argc; ++i) {
        int status = 0;

        pid_t pid = fork();

        if (pid < 0) {
            err(1, "%s", ERROR_FORK);
        }

        if (pid == 0) {
            executingCommandSafe(argv[i], argv[i]);

            exit(EXIT_SUCCESS);
        } else {
            executingCommandWait(&status);

            char buffer[1024] = { 0 };

            int length = snprintf(buffer, sizeof(buffer), "Command %d exited with status: %d!\n", i, WEXITSTATUS(status));

            writingSafe("Standard Output", 1, buffer, sizeof(char) * length);
        }
    }

    exit(EXIT_SUCCESS);
}



void writingSafe(const char* filePath, int descriptor, const void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        err(2, "%s: %s", ERROR_FILE_W, filePath);
    }
}



void executingCommandSafe(const char* commandPath, const char* newCommand) {
    assert(commandPath  !=  NULL);
    assert(newCommand   !=  NULL);

    int result = execl(commandPath, newCommand, (char*)(NULL));

    if (result < 0) {
        err(3, "%s", ERROR_EXEC);
    }
}

pid_t executingCommandWait(int* status) {
    assert(status   !=  NULL);

    int result = wait(status);

    if (result < 0) {
        err(4, "%s", ERROR_WAIT);
    }

    if (WIFEXITED(*status) == 0 && WIFSIGNALED(*status) == 0 && WIFSTOPPED(*status) == 0) {
        errx(2, "%s", ERROR_WAIT_STATUS);
    }

    return result;
}
