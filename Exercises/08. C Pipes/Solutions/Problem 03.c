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


const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_WAIT = "Error while wait command!";
const char* ERROR_PIPE = "Error while pipe command!";
const char* ERROR_EXEC = "Error while exec command!";
const char* ERROR_DUP2 = "Error while dup2 command!";



int writingSafe(const char*, int, const void*, size_t);



void dup2Safe(      int  ,       int                );
void execSafe(const char*, const char*, const char* );



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }


    int pf[2];

    if (pipe(pf) == -1) {
        err(1, "%s", ERROR_PIPE);
    }


    const pid_t pid = fork();

    if (pid < 0) {
        close(pf[0]);
        close(pf[1]);

        err(2, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        close(pf[1]);

        dup2Safe(pf[0], STDIN_FILENO);

        close(pf[0]);

        execSafe("wc", "wc", "-c");
    } else {
        close(pf[0]);

        writingSafe("Pipe Write End", pf[1], argv[1], strlen(argv[1]));

        close(pf[1]);

        if (wait(NULL) < 0) {
            err(4, "%s", ERROR_WAIT);
        }
    }

    exit(EXIT_SUCCESS);
}



void dup2Safe(int oldDescriptor, int newDescriptor) {
    int result = dup2(oldDescriptor, newDescriptor);

    if (result < 0) {
        err(6, "%s: %d to %d", ERROR_DUP2, oldDescriptor, newDescriptor);
    }
}

void execSafe(const char* command, const char* argv0, const char* argv1) {
    assert(command != NULL);

    int result = execlp(command, argv0, argv1, NULL);

    if (result < 0) {
        err(7, "%s: %s", ERROR_EXEC, command);
    }
}



int writingSafe(const char* filePath, int descriptor, const void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result < 0 || (size_t)(result) != size) {
        err(5, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
