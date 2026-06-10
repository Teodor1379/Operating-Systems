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



const char* ERROR_FILE_R = "Error while reading the file!";
const char* ERROR_FILE_W = "Error while writing the file!";


const char* ERROR_FORK = "Error while fork command!";
const char* ERROR_WAIT = "Error while wait command!"; 
const char* ERROR_PIPE = "Error while pipe command!";


const char* ERROR_WAIT_1 = "Error while wait - terminate!";
const char* ERROR_WAIT_2 = "Error while wait - exit code!";



int readingSafe(const char*, int,       void*, size_t);
int writingSafe(const char*, int, const void*, size_t);




int main(int argc, const char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }


    int descriptors[2];

    int result = pipe(descriptors);

    if (result < 0) {
        err(1, "%s", ERROR_PIPE);
    }

    
    const pid_t pid = fork();

    if (pid < 0) {
        close(descriptors[0]);
        close(descriptors[1]);

        err(2, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        close(descriptors[1]);

        while (1) {
            char c = 0;

            int reading = readingSafe("Standard Input", descriptors[0], &c, sizeof(char));

            if (reading == 0) {
                break;
            }

            writingSafe("Standard Output", 1, &c, sizeof(char));
        }

        close(descriptors[0]);

        exit(EXIT_SUCCESS);
    } else {
        close(descriptors[0]);

        writingSafe("Standard Output", descriptors[1], argv[1], sizeof(char) * strlen(argv[1]));

        close(descriptors[1]);

        int childStatus = 0;

        int result = wait(&childStatus);

        if (WIFEXITED(childStatus) == 0) {
            err(4, ERROR_WAIT_1);
        }

        if (WEXITSTATUS(childStatus) != 0) {
            err(5, ERROR_WAIT_2);
        }
    }

    exit(EXIT_SUCCESS);
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
