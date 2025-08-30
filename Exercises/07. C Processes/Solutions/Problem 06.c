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



const char* ERROR_FILE_W = "Error while writing the file!";

const char* ERROR_EXEC = "Error while execing command!";
const char* ERROR_FORK = "Error while forking command!";
const char* ERROR_WAIT = "Error while waiting command!";

const char* ERROR_WAIT_STATUS = "Error while waiting - status!";
const char* ERROR_WAIT_EXTSTS = "Error while waiting - extsts!";



int writingSafe(const char*, int, void*, size_t);



void    executingCommandSafe(const char*, const char*   );
pid_t   executingCommandWait(int*                       );



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }

    int status = 0;
    
    pid_t pid = fork();

    if (pid == -1) {
        err(1, "%s", ERROR_FORK);
    }

    if (pid > 0) {
        executingCommandWait(&status);

        char buffer[256] = { 0 };

        snprintf(buffer, sizeof(buffer), "%s\n", argv[1]);

        writingSafe("Standard Output", 1, buffer, sizeof(buffer));
    } else {
        executingCommandSafe(argv[1], argv[1]);
    }

    return 0;
}



int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        err(2, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}



void executingCommandSafe(const char* commandPath, const char* newCommand) {
    assert(commandPath  !=  NULL);
    assert(newCommand   !=  NULL);

    int result = execl(commandPath, newCommand, (char*)(NULL));

    if (result == -1) {
        err(3, "%s: %s", ERROR_EXEC, commandPath);
    }
}

pid_t executingCommandWait(int* status) {
    assert(status   !=  NULL);

    pid_t result = wait(status);

    if (result < 0) {
        err(4, "%s", ERROR_WAIT);
    }

    if (WIFEXITED(*status) == 0 && WIFSIGNALED(*status) == 0 && WIFSTOPPED(*status) == 0) {
        errx(1, "%s", ERROR_WAIT_STATUS);
    }

    if (WEXITSTATUS(*status) != 0) {
        errx(2, "%s", ERROR_WAIT_EXTSTS);
    }

    return result;
}
