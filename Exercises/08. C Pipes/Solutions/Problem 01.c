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


const char* ERROR_WAIT_1 = "Error while wait - terminate!";
const char* ERROR_WAIT_2 = "Error while wait - exit code!";



void openingSafe(const char*, int, mode_t, int* );
void closingSafe(int                            ); 



int readingSafe(const char*, int,       void*, size_t);
int writingSafe(const char*, int, const void*, size_t);



int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Expected Different Arguments!");
    }

    const char* part1 = "foo\n" ;
    const char* part2 = "bar\n" ;

    int descriptor = 0;

    openingSafe(argv[1], O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, S_IRUSR | S_IWUSR | S_IRWXU, &descriptor);

    writingSafe(argv[1], descriptor, part1, sizeof(char) * 2);

    closingSafe(descriptor);



    const pid_t pid = fork();

    if (pid < 0) {
        err(3, "%s", ERROR_FORK);
    }

    if (pid == 0) {
        openingSafe(argv[1], O_WRONLY | O_APPEND, S_IRWXU, &descriptor);

        writingSafe(argv[1], descriptor, part2, sizeof(char) * strlen(part2));

        closingSafe(descriptor);
    } else {
        int childStatus = 0;
    
        int result = wait(&childStatus);

        if (result < 0) {
            err(4, "%s", ERROR_WAIT);
        }

        if (WIFEXITED(childStatus) == 0) {
            err(4, ERROR_WAIT_1);
        }

        if (WEXITSTATUS(childStatus) != 0) {
            err(5, ERROR_WAIT_2);
        }

        openingSafe(argv[1], O_WRONLY | O_APPEND, S_IRWXU, &descriptor);

        writingSafe(argv[1], descriptor, part1 + 2, sizeof(char) * 2);

        closingSafe(descriptor);
    }

    exit(EXIT_SUCCESS);
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



int readingSafe(const char* filePath, int descriptor, void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = read(descriptor, memory, size);

    if (result < 0) {
        closingSafe(descriptor);

        err(2, "%s: %s", ERROR_FILE_R, filePath);
    }

    return result;
}

int writingSafe(const char* filePath, int descriptor, const void* memory, size_t size) {
    assert(filePath !=  NULL);
    assert(memory   !=  NULL);

    int result = write(descriptor, memory, size);

    if (result < 0 || (size_t)(result) != size) {
        closingSafe(descriptor);

        err(3, "%s: %s", ERROR_FILE_W, filePath);
    }

    return result;
}
