#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>

#include <err.h>
#include <errno.h>



const char* ERROR_FILE_W = "Error while writing the file!";

const char* ERROR_FORK = "Error while forking command!";



int writingSafe(const char* filePath, int descriptor, void* memory, size_t size);



void executeCommandFork(char);



int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
        err(1, "%s", ERROR_FORK);
    }

    if (pid > 0) {
        executeCommandFork('F');
    } else {
        executeCommandFork('S');
    }
}



int writingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result == -1 || (size_t)(result) != size) {
        errx(2, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}



void executeCommandFork(char c) {
    for (unsigned int i = 0; i < 1379; ++i) {
        writingSafe("Standard Output", 1, &c, sizeof(char));
    }

    char end = '\n';

    writingSafe("Standard Output", 1, &end, sizeof(char));
}
